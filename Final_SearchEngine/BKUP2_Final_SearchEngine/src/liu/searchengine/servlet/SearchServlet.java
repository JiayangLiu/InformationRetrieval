package liu.searchengine.servlet;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.omg.CORBA.PRIVATE_MEMBER;

import liu.searchengine.dao.IJokeDAO;
import liu.searchengine.dao.impl.JokeDAOImpl;
import liu.searchengine.dbutil.DBManager;
import liu.searchengine.factory.DAOFactory;
import liu.searchengine.lucene.IndexManager;
import liu.searchengine.lucene.JokeSearcher;
import liu.searchengine.vo.Joke;

public class SearchServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		boolean indexCreated = false;	// 是没有用的
		
		req.setCharacterEncoding("utf-8");
		resp.setContentType("text/html;charset=utf-8");
		
		String path = "search.jsp";
		String searchtext = req.getParameter("search");	// 接收search的内容
		System.out.println("Servlet: " + searchtext);
		
		List<String> result = new ArrayList<String> ();	// 保存所有返回信息
		if (searchtext==null || "".equals(searchtext)) {
			result.add("查询内容不能为空!");
		}
		
		// 创建索引
		String INDEX_PATH=SearchServlet.class.getProtectionDomain().getCodeSource().getLocation().getFile()+File.separator+"index"; 
		DBManager dbm = new DBManager();
		JokeDAOImpl daoimpl = new JokeDAOImpl(dbm.getConnection());
		if (!indexCreated) {
			try {
				DAOFactory.getIJokeInstance().getAllJoke();
			} catch (Exception e) {
				e.printStackTrace();
			}
			new IndexManager(INDEX_PATH).createIndex(JokeDAOImpl.getAll()); 
			indexCreated = true;
		}
		
		// 执行Lucene查询
		JokeSearcher searcher=new JokeSearcher(INDEX_PATH, JokeSearcher.DEFAULT_HIGHLIGHT_STYLE_pre, JokeSearcher.DEFAULT_HIGHLIGHT_STYLE_post);
		searcher.setDAOImpl(daoimpl);
		List<Joke> joke_list=searcher.getNewsByKeyWordsInHightLight(searchtext);
		for(Joke n:joke_list){
			System.out.println(n);
			result.add(n.getContent());
		}
		req.setAttribute("result", result);	// 保存错误信息
		req.getRequestDispatcher(path).forward(req, resp);	// 跳转
	}	
		
		
//		if (result.size()==0) {	// id查找成功了
//			Joke joke = new Joke();	// 实例化VO
//			joke.setContent(searchtext);
//			try {
//				if (DAOFactory.getIJokeInstance().findJoke(joke)) { // 查找成功
//					result.add(joke.getContent());
//				} else {
//					result.add("该查询内容尚未对应笑话");
//				}
//			} catch (Exception e) {
//				e.printStackTrace();
//			}
//		}
	
	
	public void doPost(HttpServletRequest req, HttpServletResponse resp)  throws ServletException, IOException {
		this.doGet(req, resp);
	}
	
	// 通过method=“get”传过来的数据，会在请求的URL里面显示; method=“post”的时候，数据不会显示在请求的URL里面显示

}
