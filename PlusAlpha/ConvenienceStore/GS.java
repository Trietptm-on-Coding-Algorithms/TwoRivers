package ConvenienceStore;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

import AboutDB.ProductDB;
import Crawling.JSONCrawling;
import Data.GiftJson;
import Data.ProductJson;
import Data.StoreData;
import Down.FileDown;
import Down.ImageDown;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonPrimitive;

public class GS {
	private static GS gs;
	private StoreData sData;
	private GS(){}
	
	//http://gs25.gsretail.com/gscvs/ko/products/event-goods-search?pageNum=&parameterList=
	//-> 1+1 parameterList->ONE_TO_ONE , TWO_TO_ONE , GIFT(������), TOTAL(��ü)
	// parameterList ������ TOTAL
	//-> pageNum :  1����
	//JSON Parsing
	
	public static synchronized GS getGS(){
		if(gs==null){
			gs=new GS();
			gs.sData=new StoreData("http://gs25.gsretail.com/gscvs/ko/products/event-goods-search?pageSize=50&pageNum="
					, "GS25", "ConvenienceStore", "http://krquddnr.cafe24.com/PlusA");
		}
		return gs;
	}
	
	public boolean gsUpdate(){
		String url=sData.getURL();
		JSONCrawling jsonCrw=JSONCrawling.getJSONCrawling();
		HashMap<String,String> typeTrans=new HashMap<String,String>();
		int numberOfPages=1;
		
		typeTrans.put("ONE_TO_ONE", "1+1");
		typeTrans.put("TWO_TO_ONE","2+1");
		typeTrans.put("GIFT", "GIFT");
		//������ GIFT��
		
		String json,sql;
		JsonObject jObject;
		ProductDB pDB=new ProductDB(sData);
		ArrayList<Object> where=new ArrayList<Object>();
		String lastUpdate=new SimpleDateFormat("yyyy-MM-dd-hh").format(new Date()); //�ð� �� ����, ������Ʈ �ð��� ��
		sData.setLastUpdate(lastUpdate);
		ImageDown imageDown=ImageDown.getImageDown();
		FileDown fd=FileDown.getFileDown();
		System.out.println("GS Update Time : "+new SimpleDateFormat("yyyy-MM-dd hh:mm:ss").format(new Date()));
		
		for(int cnt=0;cnt<numberOfPages;cnt++){
			json=jsonCrw.getJsonData(jsonCrw.crawlConnect(url+(cnt+1)));
			System.out.println("URL : "+url+(cnt+1));
			json=json.replace("\\", ""); // \ ����
			json=json.substring(1,json.length()-1); // �� ��,�� �� double quote ����
			//System.out.println("GS25 JSON : "+json);
			if(json.contains("<br")){
				cnt--;
				try {Thread.sleep(60000*11);} catch (InterruptedException e) {} //11��
				continue;
			}
			
			jObject=new JsonParser().parse(json).getAsJsonObject(); //���� ū JSON ��ü
			if(cnt==0){ // ��ü ������ �� ��������
				JsonObject jPagination=jObject.getAsJsonObject("pagination");
				JsonPrimitive jNum=jPagination.getAsJsonPrimitive("numberOfPages");
				numberOfPages=jNum.getAsInt(); //��ü ������
				System.out.println("numberOfPages : "+numberOfPages);
			}
			
			//�̹���, Ÿ��, �̸�, ����, ������Ʈ�ð�
			JsonArray productArr=jObject.getAsJsonArray("results");
			
			for(int arrCnt=0;arrCnt<productArr.size();arrCnt++){
				JsonObject productObject=productArr.get(arrCnt).getAsJsonObject(); //�迭�ȿ� ��ü�� �� ��ǰ��
				
				JsonPrimitive attFileNm=productObject.getAsJsonPrimitive("attFileNm"); //��ǰ �̹��� URL
				JsonPrimitive goodsNm=productObject.getAsJsonPrimitive("goodsNm"); //��ǰ �̸�
				JsonPrimitive price=productObject.getAsJsonPrimitive("price"); //��ǰ ����
				
				JsonObject eventTypeSp=productObject.getAsJsonObject("eventTypeSp"); // type�� ���Ե� Json ��ü
				JsonPrimitive code=eventTypeSp.getAsJsonPrimitive("code"); //type
				JsonPrimitive giftAttFileNm,giftGoodsNm,giftPrice;
				
				System.out.println(arrCnt+" - "+attFileNm.getAsString() +" "+code.getAsString()+" "+goodsNm.getAsString()+" "+price.getAsInt()+"--");
				
				where.add(sData.getBRAND_NAME()); // gs25
				where.add(imageDown.getImageFilePath(sData,fd.getFileName(attFileNm.getAsString()))); // image url
				where.add(typeTrans.get(code.getAsString())); // type
				where.add(goodsNm.getAsString()); // name
				where.add(price.getAsInt()); // price
				where.add(lastUpdate); // update
				
				if(pDB.insertData(where)) imageDown.downImage(attFileNm.getAsString(), sData);
				
				if(code.getAsString().equals("GIFT")){
					//brand,name,giftName,image,price,lastupdate
					where.clear();
					giftAttFileNm=productObject.getAsJsonPrimitive("giftAttFileNm"); //������ǰ �̹��� URL
					giftGoodsNm=productObject.getAsJsonPrimitive("giftGoodsNm"); //������ǰ �̸�
					giftPrice=productObject.getAsJsonPrimitive("giftPrice"); //������ǰ ����
					where.add(sData.getBRAND_NAME()); //gs25
					where.add(goodsNm.getAsString()); //�� ��ǰ �̸�
					where.add(giftGoodsNm.getAsString()); //������ǰ �̸�
					where.add(imageDown.getImageFilePath(sData, fd.getFileName(giftAttFileNm.getAsString()))); //������ǰ �̹��� URL
					where.add(giftPrice.getAsInt()); //������ǰ ����
					where.add(lastUpdate); //������Ʈ �ð�
					
					System.out.println(arrCnt+" + "+giftAttFileNm.getAsString() +" "+giftGoodsNm.getAsString()+" "+giftPrice.getAsInt()+"++");
					
					if(pDB.insertDataGift(where)) imageDown.downImage(giftAttFileNm.getAsString(), sData);
				}
				where.clear();
			}
		}
		
		//product table
		if(imageDown.deleteImage(sData,"product")>0){
			System.out.println("Product Image Delete OK");
			if(pDB.endingEventProductDelete(lastUpdate,"product")) System.out.println("Image DB(product) Data Delete OK");
			else System.out.println("Image DB(product) Data Delete Fail");
		}
		//gift table
		if(imageDown.deleteImage(sData,"gift")>0){
			System.out.println("Gift Image Delete OK");
			if(pDB.endingEventProductDelete(lastUpdate,"gift")) System.out.println("Image DB(gift) Data Delete OK");
			else System.out.println("Image DB(gift) Data Delete Fail");
		}
		return true;
	}

	public String gsJson(int cnt,String type){
		ProductJson pd=ProductJson.getProductJson();
		return pd.createJson(cnt, type, sData);
	}
	public String gsGiftJson(int cnt,String productName,StoreData sData){
		GiftJson giftJson=GiftJson.getGiftJson();
		return giftJson.createJson(cnt, productName, sData);
	}
	
	
	
	public StoreData getsData() {
		return sData;
	}

	public void setsData(StoreData sData) {
		this.sData = sData;
	}
	
}
