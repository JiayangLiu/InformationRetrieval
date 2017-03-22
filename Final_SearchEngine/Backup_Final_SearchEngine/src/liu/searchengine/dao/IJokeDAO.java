package liu.searchengine.dao;

import liu.searchengine.vo.Joke;

public interface IJokeDAO {
	public boolean findJoke(Joke joke) throws Exception;
}

