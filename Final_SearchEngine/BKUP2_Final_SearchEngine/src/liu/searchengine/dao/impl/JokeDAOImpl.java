package liu.searchengine.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import liu.searchengine.dao.IJokeDAO;
import liu.searchengine.vo.Joke;

public class JokeDAOImpl implements IJokeDAO {
	private Connection conn = null;
	private PreparedStatement pstmt = null;
	private final static List<Joke> allJokes = new ArrayList<Joke>();

	public JokeDAOImpl(Connection conn) {
		this.conn = conn;
		// this.allJokes=new ArrayList<Joke>();
	}

	@Override
	public boolean findJoke(Joke joke) throws Exception {
		boolean flag = false;
		try {
			String sql = "SELECT content FROM data WHERE id=?";
			this.pstmt = this.conn.prepareStatement(sql); // 实例化操作
			this.pstmt.setLong(1, joke.getId());
			ResultSet rs = this.pstmt.executeQuery();
			if (rs.next()) {
				joke.setContent(rs.getString(1));
				flag = true;
			}
		} catch (Exception e) {
			throw e; // 向上抛异常
		} finally {
			if (this.pstmt != null) {
				this.pstmt.close();
			}
		}
		return flag;
	}

	@Override
	public void getAllJoke() throws Exception {

		try {
			String sql = "SELECT * FROM QiuShiBaiKe.data";
			this.pstmt = this.conn.prepareStatement(sql); // 实例化操作
			ResultSet rs = this.pstmt.executeQuery();
			while (rs.next()) {
				Joke joke = new Joke(); // 重大bug的导致原因，不能写在while前，注意指针的概念
				joke.setId(rs.getInt(1));
				// System.out.print(rs.getString(2));
				joke.setContent(rs.getString(2));
				joke.setUrl(rs.getString(3));
				joke.setAuthor(rs.getString(4));
				joke.setFavor(rs.getString(5));
				joke.setComment(rs.getString(6));
				addOrUpdate(joke);
			}
		} catch (Exception e) {
			throw e; // 向上抛异常
		} finally {
			if (this.pstmt != null) {
				this.pstmt.close();
			}
		}
	}

	public void addOrUpdate(Joke n) {
		System.out.println(n.getId() + "");
		allJokes.add(n);
		if (allJokes.size() < 4) {
			for (int i = 0; i < allJokes.size(); i++) {
				System.out.println(allJokes.get(i).getContent());
			}
		}
		// System.out.println("list 0 test: " + allJokes.get(0).getContent());
	}

	public void delete(String id) {
		allJokes.remove(id);
	}

	public static List<Joke> getAll() {
		// System.out.println("getAll被调用了");
		// System.out.println("getAll test: " + allJokes.get(40).getContent());
		return allJokes;
	}

	public static Joke getJoke(String id) {
		// System.out.println("id is: " + id);
		return allJokes.get(Integer.parseInt(id) - 1);
	}

}
