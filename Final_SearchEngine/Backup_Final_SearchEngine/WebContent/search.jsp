<%@page import="java.util.*"%>
<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>搜索引擎第一次尝试</title>
</head>
<script language="JavaScript">

</script>
<body>
<h2>笑话查询</h2>
<%
	request.setCharacterEncoding("GBK");	// 进行乱码处理
%>
<form action="SearchServlet" method="post" onSubmit="return true">
笑话ID: <input type="text" name="id">
<input type="submit" value="查询">
</form>
<%
	List<String> info = (List<String>) request.getAttribute("info");	// 取得属性
	if (info != null) {	//判断是否有内容
		Iterator<String> iter = info.iterator();	// 实例化Iterator
		while (iter.hasNext()) {
%>
	<h4><%=iter.next()%></h4>
<%
		}
	}
%>

</body>
</html>