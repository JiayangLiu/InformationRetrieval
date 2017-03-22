package test_lucene;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class NewsService {
	private final Map<String,News> allNews=new HashMap<String, News>();
	public NewsService() {
		super(); 
			News n=new News();
			n.setId("1");
			n.setTitle("bob,机智,幽默,阳光,帅");
			n.setContent(n.getTitle()+"瞬间将猴子请来的逗必——RuBLong搞定。你们不要迷恋他，他只是个传说");
			n.setAuthor("XiaoA");
			n.setUrl("http://localhost:8080/flowershop/goods/"+1+".htm");
			n.setDate(new Date(System.currentTimeMillis()));
			addOrUpdate(n);
			
			n=new News();
			n.setId("2");
			n.setTitle("bill,脑残,逗必,众叛亲离");
			n.setContent(n.getTitle()+"瞬间将猴子请来的逗必——WeiSuoDi搞定。你们不要迷恋他，他只是个传说");
			n.setAuthor("XiaoB");
			n.setUrl("http://localhost:8080/flowershop/goods/"+1+".htm");
			n.setDate(new Date(System.currentTimeMillis()));
			addOrUpdate(n);
			
			n=new News();
			n.setId("3");
			n.setTitle("blue,正常人");
			n.setContent(n.getTitle()+"瞬间将猴子请来的逗必——LQ搞定。你们不要迷恋他，他只是个传说");
			n.setAuthor("XiaoM");
			n.setUrl("http://localhost:8080/flowershop/goods/"+1+".htm");
			n.setDate(new Date(System.currentTimeMillis()));
			addOrUpdate(n);
			
			n=new News();
			n.setId("4");
			n.setTitle("pool,路人甲,机智,幽默,阳光,帅,脑残,逗必,众叛亲离,正常人,除非搜索名字，否则他一直出现");
			n.setContent(n.getTitle()+"瞬间将猴子请来的逗必——DaTou搞定。你们不要迷恋他，他只是个传说");
			n.setAuthor("XiaoM");
			n.setUrl("http://localhost:8080/flowershop/goods/"+1+".htm");
			n.setDate(new Date(System.currentTimeMillis()));
			addOrUpdate(n); 
	}
	public void addOrUpdate(News n){
		allNews.put(n.getId(), n);
		System.out.println(get("1").getContent());
	} 
	public void delete(String id){
		allNews.remove(id);
	}
	public List<News> getAll(){
		List<News> news=new ArrayList<News>();
		Iterator<String> it=allNews.keySet().iterator();
		while(it.hasNext()){
			news.add(get(it.next()));
			System.out.println(get(it.next()).getContent());
		}
		return news;
	}
	public News get(String id){
		return allNews.get(id);
	}
}
