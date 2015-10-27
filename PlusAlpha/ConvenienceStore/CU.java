package ConvenienceStore;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import AboutDB.DBClose;
import AboutDB.DBConnect;
import AboutDB.ProductDB;
import Crawling.HTMLCrawling;
import Data.JSONCreate;
import Data.ProductJson;
import Data.StoreData;
import Down.FileDown;
import Down.ImageDown;

public class CU {
	private static CU cu;
	private CU(){}
	private StoreData sData;
	public static synchronized CU getCU(){
		if(cu==null){
			cu=new CU();
			cu.sData=new StoreData("http://cu.bgfretail.com/event/plusAjax.do?pageIndex=","CU", "ConvenienceStore","http://krquddnr.cafe24.com/PlusA");
		}
		return cu;
	}
	//10���� ������ ���� �ϱ� ���� cnt �� �������� �����Ͱ� �� ��° ���������� Ȯ��
	//type ���� �ش� Ÿ�� ������ ������
	//type ==null -> cu ��� ��ǰ
	
	public String cuJson(int cnt,String type){
		ProductJson pd=ProductJson.getProductJson();
		return pd.createJson(cnt, type, sData);
	}
	
	public boolean cuUpdate(){
		//CU
		//http://cu.bgfretail.com/event/plusAjax.do?pageIndex=1
		//pageIndex=1,2,3...
		//HTML
		//������ ���� ������ üũ �ʿ�
		//image �ٿ� ��� ../webapps/PlusA/
		
		HTMLCrawling htmlCrw=HTMLCrawling.getHTMLCrawling();
		Elements elems=null;
		ArrayList<Object> where=new ArrayList<Object>();
		ImageDown iDown=ImageDown.getImageDown();
		FileDown fd=FileDown.getFileDown();
		Document doc;
		ProductDB pDB=new ProductDB(sData);
		String lastUpdate=new SimpleDateFormat("yyyy-MM-dd-HH").format(new Date());
		sData.setLastUpdate(lastUpdate);
		
		System.out.println("CU Update Time : "+new SimpleDateFormat("yyyy-MM-dd-hh:mm:ss").format(new Date()));
		
		
		for(int i=0;;i++){
			doc=htmlCrw.crawlConnect(sData.getURL()+(i+1));
			if(!doc.toString().contains("ul")){System.out.println("-END-"); break;}
			else elems=htmlCrw.getData(doc,"ul li");
			
			System.out.println("- "+sData.getURL()+(i+1));
			
			int cnt=1;
			for(Element elem:elems){
				if(cnt++%2!=0){ // ul li �ȿ� ul li �ϳ� �� ���� �׷��� �ɷ���
					where.add(sData.getBRAND_NAME());
					where.add(iDown.getImageFilePath(sData, fd.getFileName(elem.getElementsByTag("img").attr("src"))));//�̹����� �ٿ� �� ��ġ
					where.add(elem.getElementsByTag("ul").text());
					where.add(elem.getElementsByClass("prodName").text());
					where.add(Integer.parseInt(elem.children().get(2).children().get(0).text().replace(",", "")));
					where.add(lastUpdate);
					
					if(pDB.insertData(where)) iDown.downImage(elem.getElementsByTag("img").attr("src"), sData); //�ٿ�
					else return false;
					where.clear();
				}
			}
		}
		
		//�̹��� ���� �� ��� ����
		//�����Ǵ� �̹����� �ϳ��� �ִٸ� ��񿡼��� �ش� ��ǰ ���� �ʿ�
		if(iDown.deleteImage(sData,"product")>0){
			System.out.println("Image Delete OK");
			if(pDB.endingEventProductDelete(lastUpdate,"product")) System.out.println("Image DB(product) Data Delete OK");
			else System.out.println("Image DB(product) Data Delete Fail");
		}
		return true;
	}

	public StoreData getsData() {
		return sData;
	}

	public void setsData(StoreData sData) {
		this.sData = sData;
	}
	
	
}
