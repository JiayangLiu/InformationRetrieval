package liu.searchengine.servlet;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.catalina.User;

import liu.searchengine.factory.DAOFactory;
import liu.searchengine.vo.Joke;

public class SearchServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		String path = "search.jsp";
		Integer id = Integer.parseInt(req.getParameter("id"));	// 接收id的内容 (Integer有别于int在于默认值已知为null)
		List<String> info = new ArrayList<String> ();	// 保存所有返回信息
		if (id==null || "".equals(id)) {
			info.add("ID不能为空!");
		}
		if (info.size()==0) {	// id查找成功了
			Joke joke = new Joke();	// 实例化VO
			joke.setId(id);
			try {
				if (DAOFactory.getIJokeInstance().findJoke(joke)) { // 查找成功
					info.add(joke.getContent());
				} else {
					info.add("该id尚未对应笑话");
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		req.setAttribute("info", info);	// 保存错误信息
		req.getRequestDispatcher(path).forward(req, resp);	// 跳转
	}
	
	public void doPost(HttpServletRequest req, HttpServletResponse resp)  throws ServletException, IOException {
		this.doGet(req, resp);
	}

}
