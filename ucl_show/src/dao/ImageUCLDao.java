package dao;

import entity.DetectInfo;
import entity.UCLInfo;
import utils.DBHelper;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

public class ImageUCLDao {
    // 图片中是否检测出目标对象
    public boolean hasObject(String imgName) {
        Connection conn;
        ResultSet rs = null;
        boolean hasObj = false;
        PreparedStatement stmt = null;
        String sql = "SELECT hasObject FROM ssd_detect_res WHERE imageName='" + imgName + "';"; // SQL语句
        try {
            conn = DBHelper.getConnection();
            stmt = conn.prepareStatement(sql);
            rs = stmt.executeQuery();
            if (rs.next()) {
                hasObj = rs.getBoolean("hasObject");
            }
            return hasObj;
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;
        } finally {
            // 释放数据集对象
            releaseResStmt(rs, stmt);
        }
    }

    // 获取该图片检测出的所有对象
    public ArrayList<DetectInfo> getDetectRes(String imageName) {
        Connection conn;
        PreparedStatement stmt = null;
        String sql = "SELECT objectClass,localXMIN,localYMIN,localXMAX,localYMAX,score FROM " +
                "ssd_detect_res WHERE imageName='" + imageName + "';"; // SQL语句
        ResultSet rs = null;
        ArrayList<DetectInfo> list = new ArrayList<>(); // 商品集合
        try {
            conn = DBHelper.getConnection();
            stmt = conn.prepareStatement(sql);
            rs = stmt.executeQuery();
            while (rs.next()) {
                DetectInfo detectInfo = new DetectInfo();
                detectInfo.setObjectClass(rs.getString("objectClass"));
                detectInfo.setLocalXMIN(rs.getInt("localXMIN"));
                detectInfo.setLocalYMIN(rs.getInt("localYMIN"));
                detectInfo.setLocalXMAX(rs.getInt("localXMAX"));
                detectInfo.setLocalYMAX(rs.getInt("localYMAX"));
                detectInfo.setScore(rs.getFloat("score"));
                list.add(detectInfo);
            }
            return list;
        } catch (Exception ex) {
            ex.printStackTrace();
            return null;
        } finally {
            // 释放数据集对象
            releaseResStmt(rs, stmt);
        }
    }

    // 获取图片的字节信息
    public float getImageByte(String imageName) {
        float imageByte = 0.0f;
        Connection conn;
        PreparedStatement stmt = null;
        String sql = "SELECT imageByte FROM image_byte WHERE imageName='" + imageName + "';"; // SQL语句
        ResultSet rs = null;
        try {
            conn = DBHelper.getConnection();
            stmt = conn.prepareStatement(sql);
            rs = stmt.executeQuery();
            if (rs.next()) {
                imageByte = rs.getFloat("imageByte");
            }
            return imageByte;
        } catch (Exception ex) {
            ex.printStackTrace();
            return imageByte;
        } finally {
            // 释放数据集对象
            releaseResStmt(rs, stmt);
        }
    }

    // 获取UCL_BT信息
    public UCLInfo getUCLInfo(String imageName) {
        Connection conn;
        PreparedStatement stmt = null;
        String sql = "SELECT ucl,uclSign,uclKByte,uclTimeStamp FROM ucl_bt WHERE imageName='" + imageName + "';"; // SQL语句
        ResultSet rs = null;
        UCLInfo uclInfo = new UCLInfo();
        try {
            conn = DBHelper.getConnection();
            stmt = conn.prepareStatement(sql);
            rs = stmt.executeQuery();
            if (rs.next()) {
                uclInfo.setUcl(rs.getString("ucl"));
                uclInfo.setUclSign(rs.getString("uclSign"));
                uclInfo.setUclKByte(rs.getFloat("uclKByte"));
                uclInfo.setUclTimeStamp(rs.getString("uclTimeStamp"));
            }
            return uclInfo;
        } catch (Exception ex) {
            ex.printStackTrace();
            return uclInfo;
        } finally {
            // 释放数据集对象
            releaseResStmt(rs, stmt);
        }
    }

    // 释放数据集对象及语句对象
    public void releaseResStmt(ResultSet rs, PreparedStatement stmt) {
        if (rs != null) {
            try {
                rs.close();
                rs = null;
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
        // 释放语句对象
        if (stmt != null) {
            try {
                stmt.close();
                stmt = null;
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ImageUCLDao imageUCLDao = new ImageUCLDao();
        UCLInfo res = imageUCLDao.getUCLInfo("000000");
        System.out.println(res);
        long time = System.currentTimeMillis();
        System.out.println(time);
        String timeHex = Long.toHexString(time);
        System.out.println(timeHex);
    }
}
