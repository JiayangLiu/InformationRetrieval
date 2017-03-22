package test_lucene;

import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.Sort;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.search.highlight.Formatter;
import org.apache.lucene.search.highlight.Fragmenter;
import org.apache.lucene.search.highlight.Highlighter;
import org.apache.lucene.search.highlight.InvalidTokenOffsetsException;
import org.apache.lucene.search.highlight.QueryScorer;
import org.apache.lucene.search.highlight.SimpleHTMLFormatter;
import org.apache.lucene.search.highlight.SimpleSpanFragmenter;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

public class NewsSearcher {
	public static final Version CURRENT_VERSION=Version.LUCENE_35;
	public static final String DEFAULT_HIGHLIGHT_STYLE_pre="<strong>";//高亮的HTML前缀
	public static final String DEFAULT_HIGHLIGHT_STYLE_post="</strong>";//后缀
	private NewsService newsService;
	private Analyzer defaultAnalyzer=new StandardAnalyzer(CURRENT_VERSION);
	private IndexSearcher indexSearcher;
	private QueryParser queryParser;
	private Highlighter highlighter;
	private Formatter formatter;
	public NewsSearcher(String indexPath,String pre,String post) {
		IndexReader reader = null;
		try {
			reader = IndexReader.open(FSDirectory.open(new File(indexPath)));
			indexSearcher=new IndexSearcher(reader);
			queryParser=new QueryParser(CURRENT_VERSION, "title", defaultAnalyzer);
		} catch (CorruptIndexException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		//1,利用高亮前后缀初始化一个SimpleHTMLFormatter
		formatter=new SimpleHTMLFormatter(pre, post);
	}
	public List<News> getNewsByKeyWordsInHightLight(String keyWord){
		List<News> news=new ArrayList<News>();
		try {
			Query query=queryParser.parse(keyWord);
			System.out.println(query);
			TopDocs topDocs=indexSearcher.search(query, 100);
			ScoreDoc[] scoreDocs=topDocs.scoreDocs;
			System.err.println("totalHits:"+topDocs.totalHits);
			if(topDocs.totalHits>0){
				//2,初始化QueryScorer与Fragmenter
				QueryScorer queryScorer=new QueryScorer(query);
				Fragmenter fragmenter=new SimpleSpanFragmenter(queryScorer);
				//3,初始化highlighter并设置fragmenter
				highlighter=new Highlighter(formatter, queryScorer);
				highlighter.setTextFragmenter(fragmenter);
				for(int i=0;i<scoreDocs.length;i++){
					Document doc=indexSearcher.doc(scoreDocs[i].doc);
					News n=newsService.get(doc.get("id"));
					//4,获取加入高亮前后缀后的文本
					n.setTitle(highlighter.getBestFragment(defaultAnalyzer, "title", doc.get("title")));
					news.add(n);
				}
			}
		} catch (ParseException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InvalidTokenOffsetsException e) {
			e.printStackTrace();
		}
		return news;
	}
	
	public NewsService getNewsService() {
		return newsService;
	}
	public void setNewsService(NewsService newsService) {
		this.newsService = newsService;
	}
	@Override
	protected void finalize() throws Throwable {
		this.indexSearcher.close();
		super.finalize();
	}
}
