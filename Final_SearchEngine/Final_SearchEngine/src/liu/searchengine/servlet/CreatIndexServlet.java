//package liu.searchengine.servlet;
//
//import java.io.File;
//import java.io.IOException;
//
//import javax.servlet.Servlet;
//import javax.servlet.ServletConfig;
//import javax.servlet.ServletException;
//import javax.servlet.ServletRequest;
//import javax.servlet.ServletResponse;
//
//import liu.searchengine.dao.impl.JokeDAOImpl;
//import liu.searchengine.dbutil.DBManager;
//import liu.searchengine.factory.DAOFactory;
//import liu.searchengine.lucene.IndexManager;
//
//public class CreatIndexServlet {
//	public static void main() {
//		// 创建索引
//		String INDEX_PATH = SearchServlet.class.getProtectionDomain().getCodeSource().getLocation().getFile()
//				+ File.separator + "index";
//		DBManager dbm = new DBManager();
//		JokeDAOImpl daoimpl = new JokeDAOImpl(dbm.getConnection());
//		if (!indexCreated) {
//			try {
//				DAOFactory.getIJokeInstance().getAllJoke();
//			} catch (Exception e) {
//				e.printStackTrace();
//			}
//			new IndexManager(INDEX_PATH).createIndex(JokeDAOImpl.getAll());
//			indexCreated = true;
//		}
//	}
//}
