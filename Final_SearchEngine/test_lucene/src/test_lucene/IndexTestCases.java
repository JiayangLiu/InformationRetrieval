package test_lucene;


import java.io.File;
import java.io.IOException;

import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.store.LockObtainFailedException;
import org.junit.Test;

public class IndexTestCases {
	String INDEX_PATH=IndexTestCases.class.getProtectionDomain().getCodeSource().getLocation().getFile()+File.separator+"index";
	NewsService newsService=new NewsService(); 
	@Test
	public void createIndex() throws CorruptIndexException, LockObtainFailedException, IOException{
		System.out.println("create");
			new NewsIndexManager(INDEX_PATH).createIndex(newsService.getAll()); 
	}
}
