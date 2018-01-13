<%--
  Created by IntelliJ IDEA.
  User: fly
  Date: 18-1-8
  Time: 下午2:16
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="dao.ImageUCLDao" %>
<%@ page import="entity.DetectInfo" %>
<%@ page import="entity.UCLInfo" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.text.DecimalFormat" %>
<html>
<%
    String imageNum = request.getParameter("imageNum");
    if (imageNum == null) {
        imageNum = "0";
    }
    int num = Integer.parseInt(imageNum);
    String imageName = String.format("%06d", num);
    int time = 1000;
    ImageUCLDao imageUCLDao = new ImageUCLDao();
%>
<head>
    <title>UCL_BT展示页面</title>
    <link href="css/main.css" rel="stylesheet" type="text/css"/>
    <SCRIPT LANGUAGE="JavaScript">
        function restart() {
            window.location.href = "/index.jsp";
        }
    </SCRIPT>
</head>
<body>
<div style="margin-top: 5px">
    <h1><span style="font-size: 40px">UCL_BT</span><br/>战场目标标引</h1>
    <br/>
    <div>
        <button type="button" onclick="clearTimeout(t)">暂停</button>
        <button type="button" onclick="refresh()">继续</button>
        <button type="button" onclick="restart()">重新开始</button>
    </div>
</div>

<div style="margin: 0 auto">
    <table style="margin: 0 auto" border="0" cellspacing="10" cellpadding="0">
        <tr>
            <td>
                <p>原图<br/><span style="font-size: 20px">Original Drawing</span></p>
            </td>
            <td>

            </td>
            <td>
                <p>检测图<br/><span style="font-size: 20px">Design Sketch</span></p>
            </td>

        </tr>
        <tr>
            <td>
                <%
                    String imagePath = "/images/origin/" + imageName + ".jpg";
                %>
                <img width="512" height="256" src=<%=imagePath%>>
            </td>
            <td>
                <img src="images/arrow.png">
            </td>
            <td>
                <%
                    imagePath = "/images/handled/" + imageName + ".jpg";
                %>
                <img width="512" height="256" src=<%=imagePath%>>
            </td>
        </tr>
    </table>
</div>
<div>
    <div class="clearfix" style="margin: 0 auto;">
        <p style="float: left;">目标检测结果:</p>
    </div>
    <table style="margin: 0 auto;background-color: powderblue;text-align: left;" border="2" cellspacing="1"
           cellpadding="5">
        <tr style="background-color: #4ee0ed">
            <td>
                <p style="font-size: 20px">Class</p>
            </td>
            <td>
                <p style="font-size: 20px">(localXMIN,localYMIN)</p>
            </td>
            <td>
                <p style="font-size: 20px">(localXMAX,localYMAX)</p>
            </td>
            <td>
                <p style="font-size: 20px">Confidence</p>
            </td>
        </tr>
        <%
            if (imageUCLDao.hasObject(imageName)) {
                ArrayList<DetectInfo> detectInfos = imageUCLDao.getDetectRes(imageName);
                for (DetectInfo detectInfo : detectInfos) {
        %>
        <tr>
            <td>
                <p style="font-size: 20px"><%=detectInfo.getObjectClass()%>
                </p>
            </td>
            <td>
                <p style="font-size: 20px">(<%=detectInfo.getLocalXMIN()%>,<%=detectInfo.getLocalYMIN()%>)</p>
            </td>
            <td>
                <p style="font-size: 20px">(<%=detectInfo.getLocalXMAX()%>,<%=detectInfo.getLocalYMAX()%>)</p>
            </td>
            <td>
                <p style="font-size: 20px"><%=detectInfo.getScore()%>
                </p>
            </td>
        </tr>
        <%
                }
            } else {
            }
        %>
    </table>
</div>
<br/>
<%
    UCLInfo uclInfo = imageUCLDao.getUCLInfo(imageName);
%>
<div>
    <div class="clearfix" style="margin: 0 auto">
        <p style="float: left;">UCL_BT封装:&nbsp&nbsp&nbsp</p>
    </div>
    <div style="margin: 0 auto">
    <textarea rows="4" cols="75%" style="font-size: 22px;text-align: left;color: #575757;background-color: PeachPuff"><%=uclInfo.getUcl()%>
    </textarea>
    </div>
</div>
<div class="clearfix">
    <p style="float: left;">ECDSA签名结果:&nbsp&nbsp&nbsp</p>
    <p style="float: left;font-size: 22px;max-width: 70%;text-align: left;margin-top: 35px"><%=uclInfo.getUclSign()%>
    </p>
</div>
<div class="clearfix">
    <form>
        <div class="field-label" style="margin: 0 auto"><label>数据大小:&nbsp&nbsp&nbsp</label></div>
        <div class="field-label" style="margin: 0 auto"><label style="font-size: 22px">
            原数据(图片数据)&nbsp&nbsp&nbsp</label></div>
        <%
            float imageByte = imageUCLDao.getImageByte(imageName);
        %>
        <div class="field-widget" style="margin: 0 auto"><input value="<%=imageByte%>" disabled/>
        </div>
        <div class="field-label" style="margin: 0 auto"><label style="font-size: 22px;color: #61afef;">
            (KB)&nbsp&nbsp&nbsp</label></div>
        <div class="field-label" style="margin: 0 auto"><label style="font-size: 22px">
            &nbsp&nbsp&nbsp&nbsp&nbsp&nbspUCL_BT&nbsp&nbsp&nbsp</label></div>
        <%
            String uclKByte = String.format("%.3f", uclInfo.getUclKByte());
        %>
        <div class="field-widget" style="margin: 0 auto"><input value="<%=uclKByte%>" disabled/>
        </div>
        <div class="field-label" style="margin: 0 auto"><label style="font-size: 22px;color: #61afef;">
            (KB)</label></div>
    </form>
</div>
<br/>
<div>
    <div class="clearfix" style="margin: 0 auto;">
        <p style="float: left;">UCL_BT Code部分展示:</p>
    </div>
    <table style="margin: 0 auto;background-color: powderblue;text-align: left;" border="2" cellspacing="1"
           cellpadding="5">
        <tr>
            <td>
                <p style="text-align: left;font-size: 20px;">时间戳</p>
            </td>
            <td>
                <%
                    String uclTimeStamp = uclInfo.getUclTimeStamp();
                %>
                <p style="text-align: left;font-size: 20px;"><%=uclTimeStamp%>(H)</p>
            </td>
        </tr>
        <tr>
            <td>
                <p style="text-align: left;font-size: 20px;">版本</p>
            </td>
            <td>
                <p style="text-align: left;font-size: 20px;">001(B)</p>
            </td>
        </tr>
        <tr>
            <td>
                <p style="text-align: left;font-size: 20px;">媒体类型</p>
            </td>
            <td>
                <p style="text-align: left;font-size: 20px;">00000(B)</p>
            </td>
        </tr>
        <tr>
            <td>
                <p style="text-align: left;font-size: 20px;">优先级与策略</p>
            </td>
            <td>
                <p style="text-align: left;font-size: 20px;">10100111(B)</p>
            </td>
        </tr>
        <tr>
            <td>
                <p style="text-align: left;font-size: 20px;">一级类别</p>
            </td>
            <td>
                <p style="text-align: left;font-size: 20px;">00111111(B)</p>
            </td>
        </tr>
        <tr>
            <td>
                <p style="text-align: left;font-size: 20px;">二级类别</p>
            </td>
            <td>
                <p style="text-align: left;font-size: 20px;">00000001(B)</p>
            </td>
        </tr>
    </table>
</div>
<%--<div>--%>
<%--<div class="clearfix" style="margin: 0 auto">--%>
<%--<p style="float: left;text-align:left">UCL_BT Property部分展示(其中一个目标)：</p>--%>
<%--</div>--%>
<%--<p>UCL_BT Property部分</p>--%>
<%--</div>--%>
<%
    num++;
    if (num == 1000) {
%>
<SCRIPT LANGUAGE="JavaScript">
    alert("演示结束！");
</SCRIPT>
<%
        return;
    }
%>
<SCRIPT LANGUAGE="JavaScript">

    <!--
    function refresh() {
        <%
            String url = "/index.jsp?imageNum=" +num;
        %>
        window.location.href = "<%=url%>";
    }

    var t = setTimeout("refresh()", <%=time%>);
    //-->
</SCRIPT>
</body>
</html>
