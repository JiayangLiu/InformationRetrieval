package liu.searchengine.dbutil;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DBManager {
	private Connection conn;
	private PreparedStatement pstmt;
	
	// 加载驱动类
	public DBManager(){
		try {
			Class.forName("com.mysql.jdbc.Driver");
			this.conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/QiuShiBaiKe", "root", "root"); // 3306是MySQL
		} catch (ClassNotFoundException | SQLException e) {
			e.printStackTrace();
		}
	}
	
	// 取得数据库连接
	public Connection getConnection() {
		return this.conn;
	}
	
	// 关闭数据库
	public void close() throws Exception {
		if (this.conn != null) {	// 避免NullPointerException
			this.conn.close();
		}
	}
}
