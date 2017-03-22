package liu.searchengine.dao.proxy;

import liu.searchengine.dao.IJokeDAO;
import liu.searchengine.dao.impl.JokeDAOImpl;
import liu.searchengine.dbutil.DBManager;
import liu.searchengine.vo.Joke;

public class JokeDAOProxy implements IJokeDAO { // 定义DAO代理操作类
	private DBManager dbm = null;
	private IJokeDAO dao = null;
	
	public JokeDAOProxy() {
		this.dbm = new DBManager();
		this.dao = new JokeDAOImpl(this.dbm.getConnection());
	}
	
	
	@Override
	public boolean findJoke(Joke joke) throws Exception {
		boolean flag = false;
		try {
			flag = this.dao.findJoke(joke);	// 调用真实主题
		} catch (Exception e) {
			throw e;	// 向上抛异常
		} finally {
			this.dbm.close();
		}
		return flag;
	}

	@Override
	public void getAllJoke() throws Exception {
		try {
			this.dao.getAllJoke();	// 调用真实主题
		} catch (Exception e) {
			throw e;	// 向上抛异常
		} finally {
			this.dbm.close();
		}
	}

}
