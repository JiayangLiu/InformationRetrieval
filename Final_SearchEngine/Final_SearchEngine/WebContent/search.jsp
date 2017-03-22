<%@page import="java.util.*"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
  <title>Just Kidding!</title>

  <!-- Bootstrap -->
  <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet">
  <script src="bootstrap/js/bootstrap.min.js"></script>
  <script src="http://cdn.bootcss.com/jquery/1.11.3/jquery.min.js"></script>

  <link rel="stylesheet" href="listview.css" type="text/css" />
  <link rel="stylesheet" href="full_screen_search.css" type="text/css" />
  <script type="text/javascript">
    $(function() {
      $('a[href="#search"]').on('click', function(event) {
        event.preventDefault();
        $('#search').addClass('open');
        $('#search > form > input[type="search"]').focus();
      });

      $('#search, #search button.close').on('click keyup', function(event) {
        if (event.target == this || event.target.className == 'close' || event.keyCode == 27) {
          $(this).removeClass('open');
        }
      });

/*       $('form').submit(function(event) {
        event.preventDefault();
        return false;
      }) */
    });
  </script>
  	<style>
		mark {
			color: #ff3388;
			background-color: #ffffff;
			font-weight: bold;
		}
	</style>

</head>
<script language="JavaScript">
	
</script>
<body>
  <div class="container">
    <nav class="navbar navbar-default" role="navigation">
      <div class="container-fluid">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#" style="color:#ff7a00">欢迎来到Just Kidding!</a>
        </div>

        <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
          <ul class="nav navbar-nav">
            <li class="active"><a href="http://www.jeremyliu0824.com/index.php/2017/01/08/just-kidding/">设计文档</a></li>
            <!-- <li><a href="#">Link</a></li> -->
          </ul>
          <ul class="nav navbar-nav navbar-right">
            <li><a href="#search" style="color:#ff008a">笑话搜索</a></li>
          </ul>
        </div>
      </div>
    </nav>
  </div>
  <div id="search">
    <button type="button" class="close">×</button>
    <%
		request.setCharacterEncoding("GBK"); // 进行乱码处理
   %>
<!--    <form action="SearchServlet" method="post" onSubmit="return true">
     <input type="text" name="search"> <input type="submit"
     value="查询">
   </form> -->
    <form action="SearchServlet" method="post" onSubmit="return true">
     <input type="search" value="" name="search" placeholder="寡人今天想听..." />
          <button type="submit" class="btn btn-success">嘿嘿嘿</button>
     </form>
      </div>
      
      <ul class="surveys grid">

       <%
		List<String> result = (List<String>) request.getAttribute("result"); // 取得属性
		List<String> result_href = (List<String>) request.getAttribute("result_href");
		List<String> result_favor = (List<String>) request.getAttribute("result_favor");
		List<String> result_comment = (List<String>) request.getAttribute("result_comment");
		if (result != null) { 	//判断是否有内容
			Iterator<String> iter = result.iterator(); // 实例化Iterator
			Iterator<String> iter_href = result_href.iterator();
			Iterator<String> iter_favor = result_favor.iterator();
			Iterator<String> iter_comment = result_comment.iterator();
			
			while (iter.hasNext()) {
				String percent = Integer.parseInt(iter_favor.next())/100 + "";
       %>
     <li class="survey-item">
      
      <div style="height:80px; word-wrap:break-word; overflow:hidden; text-overflow:ellipsis; border:1px">
      	<a href="<%=iter_href.next()%>" class="survey-name"><%=iter.next()%></a>
      </div>
      
      <span>...</span>
      
      <div class="pull-right">
        <span class="survey-progress">
          <span class="survey-progress-bg">
            <span class="survey-progress-fg" style="width: <%=percent%>%;"></span>
          </span>
          <span class="survey-progress-labels">
            <span class="survey-progress-label">
              <%=percent%>%
            </span>
            <span class="survey-completes">
              <%=iter_comment.next()%>条评论
            </span>
          </span>
        </span>
      </div>
    </li>
    
    <%
  }
}
%>
</ul>

<footer>Designed and programmed by JeremyLiu.</footer>

<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<script src="http://cdn.bootcss.com/jquery/1.11.3/jquery.min.js"></script>
<!-- Include all compiled plugins (below), or include individual files as needed -->
<script src="bootstrap/js/bootstrap.min.js"></script>
</body>
</html>