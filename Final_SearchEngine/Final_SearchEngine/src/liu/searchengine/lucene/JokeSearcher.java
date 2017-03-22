package liu.searchengine.lucene;

import java.io.File;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.List;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
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
import org.wltea.analyzer.lucene.IKAnalyzer;

import com.chenlb.mmseg4j.Dictionary;
import com.chenlb.mmseg4j.analysis.MMSegAnalyzer;

import liu.searchengine.dao.impl.JokeDAOImpl;
import liu.searchengine.vo.Joke;

public class JokeSearcher {
	public static final Version CURRENT_VERSION = Version.LUCENE_35;
	public static final String DEFAULT_HIGHLIGHT_STYLE_pre = "<mark>";// 高亮的HTML前缀
	public static final String DEFAULT_HIGHLIGHT_STYLE_post = "</mark>";// 后缀
	private JokeDAOImpl daoimpl;
	private Analyzer defaultAnalyzer;
	private IndexSearcher indexSearcher;
	private QueryParser queryParser;
	private Highlighter highlighter;
	private Formatter formatter;

	public JokeSearcher(String indexPath, String pre, String post) {
		IndexReader reader = null;
		try {
			reader = IndexReader.open(FSDirectory.open(new File(indexPath)));
			indexSearcher = new IndexSearcher(reader);
			System.out.println("新IndexSearcher创建成功");
			defaultAnalyzer = new MMSegAnalyzer(); // StandardAnalyzer(CURRENT_VERSION);
			queryParser = new QueryParser(CURRENT_VERSION, "content", defaultAnalyzer);

		} catch (CorruptIndexException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		// 1. 利用高亮前后缀初始化一个SimpleHTMLFormatter
		formatter = new SimpleHTMLFormatter(pre, post);
	}

	public List<Joke> getNewsByKeyWordsInHightLight(String keyWord) {
		System.out.println("JokeSearcher: " + keyWord);

		List<Joke> joke_list = new ArrayList<Joke>();
		try {
			Query query = queryParser.parse(keyWord);
			System.out.println("分词之后: " + query);
			TopDocs topDocs = indexSearcher.search(query, 100);
			ScoreDoc[] scoreDocs = topDocs.scoreDocs;
			System.err.println("totalHits:" + topDocs.totalHits);
			if (topDocs.totalHits > 0) {
				// 2. 初始化QueryScorer与Fragmenter
				QueryScorer queryScorer = new QueryScorer(query);
				Fragmenter fragmenter = new SimpleSpanFragmenter(queryScorer);
				// 3. 初始化highlighter并设置fragmenter
				highlighter = new Highlighter(formatter, queryScorer);
				highlighter.setTextFragmenter(fragmenter);
				for (int i = 0; i < scoreDocs.length; i++) {
					Document doc = indexSearcher.doc(scoreDocs[i].doc);
					Joke n = JokeDAOImpl.getJoke(doc.get("id"));
					// 4. 获取加入高亮前后缀后的文本
					String text;
					text = doc.get("content");
					String string = null;
					string = highlighter.getBestFragment(defaultAnalyzer, "content", text);
					n.setContent(string);
					joke_list.add(n);
				}
			}
		} catch (ParseException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InvalidTokenOffsetsException e) {
			e.printStackTrace();
		}
		try {
			finalize();
		} catch (Throwable e) {
			System.out.println("JokeSearcher finalize失败");
			e.printStackTrace();
		}
		return joke_list;
	}

	public JokeDAOImpl getDAOImpl() {
		return daoimpl;
	}

	public void setDAOImpl(JokeDAOImpl daoimpl) {
		this.daoimpl = daoimpl;
	}

	@Override
	protected void finalize() throws Throwable {
		this.indexSearcher.close();
		super.finalize();
	}
}