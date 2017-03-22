package liu.searchengine.factory;

import liu.searchengine.dao.IJokeDAO;
import liu.searchengine.dao.proxy.JokeDAOProxy;

public class DAOFactory {	// 定义工厂类
	public static IJokeDAO getIJokeInstance() {	// 取得DAO实例
		return new JokeDAOProxy();	// 返回代理实例
	}
}
