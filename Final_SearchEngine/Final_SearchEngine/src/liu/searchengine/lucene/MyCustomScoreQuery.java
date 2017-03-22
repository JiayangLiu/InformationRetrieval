package liu.searchengine.lucene;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.lucene.document.Document;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.FilterIndexReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.Term;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TermQuery;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.search.function.CustomScoreProvider;
import org.apache.lucene.search.function.CustomScoreQuery;
import org.apache.lucene.search.function.FieldScoreQuery;
import org.apache.lucene.search.function.FieldScoreQuery.Type;
import org.apache.lucene.search.function.ValueSourceQuery;
import org.apache.lucene.store.Directory;

public class MyCustomScoreQuery {
	public void searchByScoreQuery() {
		try {
			IndexSearcher searcher = new IndexSearcher(IndexReader.open(FileIndexUtils.getDirectory()));
			Query q = new TermQuery(new Term("PageRank", "rank"));
			// 创建一个评分域
			FieldScoreQuery fd = new FieldScoreQuery("PageRank", Type.INT);
			// 根据评分域和原有的Query创建自定义的Query对象
			MyCustomRankScoreQuery query = new MyCustomRankScoreQuery(q, fd);
			TopDocs tds = null;
			tds = searcher.search(query, 100);
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
			for(ScoreDoc sd:tds.scoreDocs) {
				Document d = searcher.doc(sd.doc);
			}		
			searcher.close();
		} catch (CorruptIndexException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private class MyCustomRankScoreQuery extends CustomScoreQuery {

		public MyCustomRankScoreQuery(Query subQuery, ValueSourceQuery valSrcQuery) {
			super(subQuery, valSrcQuery);
		}

		@Override
		protected CustomScoreProvider getCustomScoreProvider(IndexReader reader) throws IOException {
			// 默认情况实现的评分是原有评分+传入进来的评分域所获取来确定最终评分的
			// 为了突出链接分析得到的每个段子的PageRank进行自定义评分设定
			
			return super.getCustomScoreProvider(reader);
		}
	}
	
	private class MyCustomRankScoreProvider extends CustomScoreProvider {

		public MyCustomRankScoreProvider(IndexReader reader) {
			super(reader);
		}
		
		@Override
		public float customScore(int doc, float subQueryScore, float valSrcScore) throws IOException {
			return super.customScore(doc, subQueryScore, valSrcScore);
		}
		
	}
}
