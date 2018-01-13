# -*- coding: UTF-8 -*-

import os
import sys
import time
import caffe
import numpy as np
from timer import Timer
from db_helper import DBHelper
import matplotlib.pyplot as plt
from caffe.proto import caffe_pb2
from google.protobuf import text_format


# Load LabelMap file.
def get_labelmap(labelmap_path):
    labelmap_file = labelmap_path
    file = open(labelmap_file, 'r')
    labelmap = caffe_pb2.LabelMap()
    text_format.Merge(str(file.read()), labelmap)
    return labelmap


# get labelnames
def get_labelname(labelmap, labels):
    num_labels = len(labelmap.item)
    labelnames = []
    if type(labels) is not list:
        labels = [labels]
    for label in labels:
        found = False
        for i in xrange(0, num_labels):
            if label == labelmap.item[i].label:
                found = True
                labelnames.append(labelmap.item[i].display_name)
                break
        assert found == True
    return labelnames


# 处理输入的数据,caffe中用的图像是BGR空间,但是matplotlib用的是RGB空间
# caffe的数值空间是[0,255],但是matplotlib的空间是[0,1]
def input_process(net):
    # 定义转换输入的data数值的函数
    transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
    transformer.set_transpose('data', (2, 0, 1))  # 分离图像的RGB三通道
    transformer.set_mean('data', np.array([104, 117, 123]))  # mean pixel,减去平均像素值,从而减少噪声的影响
    transformer.set_raw_scale('data', 255)  # 将0-1空间变成0-255空间
    transformer.set_channel_swap('data', (2, 1, 0))  # 交换RGB空间到BGR空间
    image_resize = 300
    net.blobs['data'].reshape(1, 3, image_resize, image_resize)  # batchsize=1,三通道,图像大小是300*300
    return transformer


# 检测一张图片
def im_detect(transformer, labelmap, image_name, images_path, db):
    i = 0
    while os.path.exists(images_path + image_name) is False:  # 图片不存在则循环等待，超过10秒退出程序
        if i > 100:
            sys.exit()
        time.sleep(0.1)
        i += 1
    image = caffe.io.load_image(images_path + image_name)
    image_byte = os.path.getsize(images_path + image_name) / 1024.0

    # Run the net and examine the top_k results
    timer = Timer()
    timer.tic()
    transformed_image = transformer.preprocess('data', image)
    net.blobs['data'].data[...] = transformed_image  # 将图像数据拷贝到内存中并分配给网络net

    # 分类
    detections = net.forward()['detection_out']

    # 解析输出结果
    det_label = detections[0, 0, :, 1]
    det_conf = detections[0, 0, :, 2]
    det_xmin = detections[0, 0, :, 3]
    det_ymin = detections[0, 0, :, 4]
    det_xmax = detections[0, 0, :, 5]
    det_ymax = detections[0, 0, :, 6]

    # 得到置信度>=0.6的检测目标
    top_indices = [i for i, conf in enumerate(det_conf) if conf >= 0.6]
    top_conf = det_conf[top_indices]
    top_label_indices = det_label[top_indices].tolist()
    top_labels = get_labelname(labelmap, top_label_indices)
    top_xmin = det_xmin[top_indices]
    top_ymin = det_ymin[top_indices]
    top_xmax = det_xmax[top_indices]
    top_ymax = det_ymax[top_indices]

    timer.toc()
    print 'Detection took {:.3f}s for {}'.format(timer.total_time, image_name)
    image_name = image_name[:-4]
    if db.search(image_name, 'ssd_detect_res') != 0:
        db.delete_data(image_name, 'ssd_detect_res')  # 删除数据库中该图片原有的数据
    if db.search(image_name, 'image_byte') != 0:
        db.delete_data(image_name, 'image_byte')  # 删除数据库中该图片原有的数据
    db.insert_data(image_name, image_byte)
    if top_conf.shape[0] == 0:  # 图片中没有检测到目标
        if db.insert_data(image_name, 0, 1) == 0:
            print 'Insert data without object failed!'
    else:
        # 获取每个目标类别及目标的bounding box
        for i in xrange(top_conf.shape[0]):
            xmin = int(round(top_xmin[i] * image.shape[1]))
            ymin = int(round(top_ymin[i] * image.shape[0]))
            xmax = int(round(top_xmax[i] * image.shape[1]))
            ymax = int(round(top_ymax[i] * image.shape[0]))
            score = top_conf[i]
            label_name = top_labels[i]
            if i != top_conf.shape[0] - 1:
                if db.insert_data(image_name, str(label_name), xmin, ymin, xmax, ymax, score) == 0:
                    print 'Insert data with object failed!'
            else:
                if db.insert_data(image_name, str(label_name), xmin, ymin, xmax, ymax, score, 1) == 0:
                    print 'Insert data with object failed!'
            print 'class: ' + str(label_name) + ' ' + ' location: ' + str(xmin) + ' ' + str(ymin) + \
                  ' ' + str(xmax) + ' ' + str(ymax) + ' possibility: ' + str(score)

    return timer.total_time


if __name__ == '__main__':
    # Make sure that caffe is on the python path:
    caffe_root = '/home/beijing/opt/caffe/'
    os.chdir(caffe_root)
    sys.path.insert(0, 'python')
    caffe.set_device(1)  # 假如有多块gpu，选择第一块gpu
    caffe.set_mode_gpu()  # 设置用GPU来加载Caffe并且加载网络
    labelmap_path = 'data/KITTI/labelmap_kitti.prototxt'
    labelmap = get_labelmap(labelmap_path)

    # * Load the net in the test phase for inference, and configure input preprocessing.
    model_def = 'models/VGGNet/KITTI3/SSD_300x300/deploy.prototxt'
    model_weights = 'models/VGGNet/KITTI3/SSD_300x300/VGG_KITTI_SSD_300x300_iter_80000.caffemodel'

    net = caffe.Net(model_def,  # defines the structure of the model
                    model_weights,  # contains the trained weights
                    caffe.TEST)  # use test mode (e.g., don't perform dropout)
    transformer = input_process(net)

    images_path = '/mnt/disk_a/beijing/DataSet/augsburg/'
    im_names = []
    for index in range(1000):
        s = "%06d" % index
        im_names.append(str(s) + '.png')
    totaltime = 0
    db = DBHelper()
    db.get_conn()
    db.create_database()
    db.create_table()
    for image_name in im_names:
        print '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
        totaltime += im_detect(transformer, labelmap, image_name, images_path, db)
    db.close_conn()
    print 'totaltime = ' + str(totaltime) + ' for ' + str(len(im_names)) + ' images'
    print 'averagetime = ' + str(totaltime / len(im_names))
