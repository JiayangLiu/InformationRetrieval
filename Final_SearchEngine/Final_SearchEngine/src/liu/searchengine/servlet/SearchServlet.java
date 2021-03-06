package liu.searchengine.servlet;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import liu.searchengine.dao.IJokeDAO;
import liu.searchengine.dao.impl.JokeDAOImpl;
import liu.searchengine.dbutil.DBManager;
import liu.searchengine.factory.DAOFactory;
import liu.searchengine.lucene.IndexManager;
import liu.searchengine.lucene.JokeSearcher;
import liu.searchengine.vo.Joke;

public class SearchServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		boolean indexCreated = false; // 是没有用的

		req.setCharacterEncoding("utf-8");
		resp.setContentType("text/html;charset=utf-8");

		String path = "search.jsp";
		String searchtext = req.getParameter("search"); // 接收search的内容
		System.out.println("Servlet: " + searchtext);

		List<String> result = new ArrayList<String>(); // 保存所有返回信息
		if (searchtext == null || "".equals(searchtext)) {
			result.add("查询内容不能为空!");
		}
		List<String> result_href = new ArrayList<String>(); // 保存所有返回信息
		if (searchtext == null || "".equals(searchtext)) {
			result_href.add("#");
		}
		List<String> result_favor = new ArrayList<String>(); // 保存所有返回信息
		if (searchtext == null || "".equals(searchtext)) {
			result_favor.add("0");
		}
		List<String> result_comment = new ArrayList<String>(); // 保存所有返回信息
		if (searchtext == null || "".equals(searchtext)) {
			result_comment.add("0");
		}
		
		// 创建索引
		String INDEX_PATH = SearchServlet.class.getProtectionDomain().getCodeSource().getLocation().getFile()
				+ File.separator + "index";
		DBManager dbm = new DBManager();
		JokeDAOImpl daoimpl = new JokeDAOImpl(dbm.getConnection());
		if (!indexCreated) {
			try {
				DAOFactory.getIJokeInstance().getAllJoke();
			} catch (Exception e) {
				e.printStackTrace();
			}
			try {
				new IndexManager(INDEX_PATH).createIndex(daoimpl.getAll());
				System.out.println("新IndexManager创建成功");
			} catch (Throwable e) {
				System.out.println("新IndexManager创建失败");
				e.printStackTrace();
			}
			indexCreated = true;
		}

		// 执行Lucene查询
		JokeSearcher searcher = new JokeSearcher(INDEX_PATH, JokeSearcher.DEFAULT_HIGHLIGHT_STYLE_pre,
				JokeSearcher.DEFAULT_HIGHLIGHT_STYLE_post);
		searcher.setDAOImpl(daoimpl);
		List<Joke> joke_list = searcher.getNewsByKeyWordsInHightLight(searchtext);
		for (Joke n : joke_list) {
			result.add(n.getContent());
			result_href.add(n.getUrl());
			result_favor.add(n.getFavor());
			result_comment.add(n.getComment());
		}
		if (result.size() == 0) {
			result.add("搜索内容尚未有笑话对应");
			result_href.add("#");
			result_favor.add("0");
			result_comment.add("0");
		}
		req.setAttribute("result", result); // 保存信息
		req.setAttribute("result_href", result_href);
		req.setAttribute("result_favor", result_favor);
		req.setAttribute("result_comment", result_comment);
		
		// 删除索引 解决indexwrite锁问题 以及 索引多重出现问题
		System.out.println(INDEX_PATH);
		System.out.println(SearchServlet.class.getProtectionDomain().getCodeSource().getLocation().getFile());
	    deleteDirectory(INDEX_PATH);
	    daoimpl.deleteAll();
	    
		req.getRequestDispatcher(path).forward(req, resp); // 跳转
	}

	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		this.doGet(req, resp);
	}
	
	/** 
	 * 删除单个文件 
	 * @param   sPath    被删除文件的文件名 
	 * @return 单个文件删除成功返回true，否则返回false 
	 */  
	public boolean deleteFile(String sPath) {  
	    boolean flag = false;  
	    File file = new File(sPath);  
	    // 路径为文件且不为空则进行删除  
	    if (file.isFile() && file.exists()) {  
	        file.delete();  
	        flag = true;  
	    }  
	    return flag;  
	}  
	
	
	/** 
	 * 删除目录（文件夹）以及目录下的文件 
	 * @param   sPath 被删除目录的文件路径 
	 * @return  目录删除成功返回true，否则返回false 
	 */  
	public boolean deleteDirectory(String sPath) {  
	    //如果sPath不以文件分隔符结尾，自动添加文件分隔符  
	    if (!sPath.endsWith(File.separator)) {  
	        sPath = sPath + File.separator;  
	    }  
	    File dirFile = new File(sPath);  
	    //如果dir对应的文件不存在，或者不是一个目录，则退出  
	    if (!dirFile.exists() || !dirFile.isDirectory()) {  
	        return false;  
	    }  
	    boolean flag = true;  
	    //删除文件夹下的所有文件(包括子目录)  
	    File[] files = dirFile.listFiles();  
	    for (int i = 0; i < files.length; i++) {  
	        //删除子文件  
	        if (files[i].isFile()) {  
	            flag = deleteFile(files[i].getAbsolutePath());  
	            if (!flag) break;  
	        } //删除子目录  
	        else {  
	            flag = deleteDirectory(files[i].getAbsolutePath());  
	            if (!flag) break;  
	        }  
	    }  
	    if (!flag) return false;  
	    //删除当前目录  
	    if (dirFile.delete()) {  
	        return true;  
	    } else {  
	        return false;  
	    }  
	}

	// 通过method=“get”传过来的数据，会在请求的URL里面显示; method=“post”的时候，数据不会显示在请求的URL里面显示
}
