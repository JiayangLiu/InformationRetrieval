package liu.searchengine.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import org.omg.PortableServer.ID_ASSIGNMENT_POLICY_ID;

import liu.searchengine.dao.IJokeDAO;
import liu.searchengine.vo.Joke;

public class JokeDAOImpl implements IJokeDAO {
	private Connection conn = null;
	private PreparedStatement pstmt = null;
	
	public JokeDAOImpl(Connection conn) {
		this.conn = conn;
	}

	@Override
	public boolean findJoke(Joke joke) throws Exception {
		boolean flag = false;
		try {
			String sql = "SELECT content FROM data WHERE id=?";
			this.pstmt = this.conn.prepareStatement(sql);	// 实例化操作
			this.pstmt.setLong(1, joke.getId());
			ResultSet rs = this.pstmt.executeQuery();
			if (rs.next()) {
				joke.setContent(rs.getString(1));
				flag = true;
			}
		} catch (Exception e) {
			throw e;	// 向上抛异常
		} finally {
			if (this.pstmt != null) {
				this.pstmt.close();
			}
		}
		return flag;
	}
	
}
