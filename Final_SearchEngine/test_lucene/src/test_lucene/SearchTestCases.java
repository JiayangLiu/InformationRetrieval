package test_lucene;

import java.io.File;
import java.util.List;

import org.junit.Test;

public class SearchTestCases {

	String INDEX_PATH=IndexTestCases.class.getProtectionDomain().getCodeSource().getLocation().getFile()+File.separator+"index";
	NewsService newsService=new NewsService(); 
	@Test
	public void searchNews(){
		NewsSearcher searcher=new NewsSearcher(INDEX_PATH, NewsSearcher.DEFAULT_HIGHLIGHT_STYLE_pre, NewsSearcher.DEFAULT_HIGHLIGHT_STYLE_post);
		searcher.setNewsService(newsService);
		List<News> news=searcher.getNewsByKeyWordsInHightLight("机智 OR 脑残");
		for(News n:news){
			System.out.println(n);
		}
	}
}

