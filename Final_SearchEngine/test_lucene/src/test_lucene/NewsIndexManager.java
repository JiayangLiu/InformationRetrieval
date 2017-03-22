package test_lucene;

import java.io.File;
import java.io.IOException;
import java.util.List;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.Field.Index;
import org.apache.lucene.document.Field.Store;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.index.IndexWriterConfig.OpenMode;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.store.LockObtainFailedException;
import org.apache.lucene.util.Version;

public class NewsIndexManager {
	public static final Version CURRENT_VERSION=Version.LUCENE_35;
	private IndexWriter indexWriter;
	private IndexWriterConfig conf;
	private Analyzer defaultAnalyzer;
	private Directory indexDirectory;
	public NewsIndexManager(String indexPath) throws CorruptIndexException, LockObtainFailedException, IOException {
		super();
		indexDirectory=FSDirectory.open(new File(indexPath));
		defaultAnalyzer=new StandardAnalyzer(CURRENT_VERSION);
		this.conf=new IndexWriterConfig(CURRENT_VERSION,defaultAnalyzer);
		conf.setOpenMode(OpenMode.CREATE);
		indexWriter=new IndexWriter(indexDirectory, conf);
	}
	//对JavaBean索引
	public synchronized void createIndex(List<News> news){
		Field idField,titleField,contentField,authorField,dateField;
		News n;
		Document doc;
		for(int i=0;i<news.size();i++){
			n=news.get(i);
			idField=new Field("id",n.getId(),Store.YES,Index.NOT_ANALYZED);
			idField.setBoost(0.0001F);
			titleField=new Field("title",n.getTitle(),Store.YES,Index.ANALYZED);
			contentField=new Field("content",n.getContent(),Store.NO,Index.ANALYZED);
			authorField=new Field("author",n.getAuthor(),Store.YES,Index.NOT_ANALYZED);
			dateField=new Field("date",n.getDate().getTime()+"",Store.YES,Index.NO);
			doc=new Document();
			doc.add(idField);
			doc.add(titleField);
			doc.add(contentField);
			doc.add(authorField);
			doc.add(dateField);
			System.out.println(n);
			try {
				indexWriter.addDocument(doc);
			} catch (CorruptIndexException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		try {
			indexWriter.commit();
		} catch (CorruptIndexException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	@Override
	protected void finalize() throws Throwable {
		indexWriter.close();
		super.finalize();
	}
}