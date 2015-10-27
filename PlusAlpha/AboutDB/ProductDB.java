package AboutDB;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import Data.StoreData;

public class ProductDB {
	
	private StoreData sData;
	
	public ProductDB(StoreData sData){
		this.sData=sData;
	}
	
	//brand,image,type,name,price,lastupdate
	//product �� Ű��=brand+name
	//�ߺ��Ǵ� Ű���� ������ �ش� ���� ���� ������Ʈ(image,type,price,lastupdate)
	//Ű���� ������ �߰�
	public boolean insertData(ArrayList<Object> where){
		String sql="insert into product values(?,?,?,?,?,?) on duplicate key update image=?, type=?,price=?,lastupdate=?";
		DBConnect db=DBConnect.getDBConnect();
		ArrayList<Object> insertWhere=new ArrayList<Object>();
		insertWhere.addAll(where);
		insertWhere.add(where.get(1)); //image
		insertWhere.add(where.get(2)); //type
		insertWhere.add(where.get(4)); //price
		insertWhere.add(where.get(5)); //lastupdate
		
		if(db.modifyDB(sql, insertWhere)){
			System.out.println(sData.getBRAND_NAME()+" : "+where.get(3)+" Data Insert OR Update OK");
			return true;
		}
		else{
			System.out.println(sData.getBRAND_NAME()+" Data Insert Error");
			return false;
		}
	}
	
	//�� ���������� ������� -> ��� ����
	//��� ���� ��ǰ DB ���� �ʿ�
	//DB�� ���� �� �������� ��ǰ �����͸� ��
	//DB�� �� �� �� �������� ��ǰ �����Ϳ� �ش��ϴ� ���� ������ �װ��� ����
	// => �ֱ� ������Ʈ ��¥ ������ 
	
	public boolean endingEventProductDelete(String lastUpdate,String table){
		DBConnect db=DBConnect.getDBConnect();
		String sql="delete from "+table+" where lastupdate!="+lastUpdate+" brand="+sData.getBRAND_NAME();
		if(db.modifyDB(sql, null)){
			System.out.println("Old Data Delete");
			return true;
		}
		else{
			System.out.println("Old Data Delete Fail");
			return false;
		}
	}
	
	public boolean insertDataGift(ArrayList<Object> where){
		//brand 0,name 1 , giftname 2 ,image 3 ,price 4 ,lastupdate 5
		DBConnect db=DBConnect.getDBConnect();
		String sql="insert into gift values(?,?,?,?,?,?) on duplicate key update giftname=?,image=?,price=?,lastupdate=?";
		ArrayList<Object> insertWhere=new ArrayList<Object>();
		insertWhere.addAll(where);
		insertWhere.add(where.get(2));
		insertWhere.add(where.get(3));
		insertWhere.add(where.get(4));
		insertWhere.add(where.get(5));
		
		if(db.modifyDB(sql, insertWhere)){
			System.out.println(where.get(0) + " : " + where.get(1) + " + "+where.get(2) + " Data Insert OR Update OK");
			return true;
		}
		else {
			System.out.println(where.get(0) + " : " + where.get(1) + " + "+where.get(2) + " Data Insert OR Update Fail");
			return false;
		}
	}

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//checkUpdate �ʿ� ������
	//insertData �޼ҵ忡�� �ߺ� üũ �� ���� �Ǵ� ������ ��.
	
	public boolean checkUpdate(ArrayList<Object>where){
		DBConnect db=DBConnect.getDBConnect();
		String sql="select count(*) from product where image=?"; //image ���� URL�̶� Ÿ ��ǰ�� �ߺ� ����..�Ƹ���..
		ArrayList<Object> checkWhere=new ArrayList<Object>();
		checkWhere.add(where.get(1));
		ResultSet rs=db.selectDB(sql, checkWhere);
		System.out.println("checkWhere : "+where.get(1));
		
		try {
			rs.next();
			int cnt;
			if((cnt=rs.getInt(1))>0){
				System.out.println(where.get(3)+" : duplication "+cnt);
				return false;
			}
			else{
				System.out.println(cnt);
				return true;
			}
		} catch (SQLException e) {
			System.out.println(sData.getBRAND_NAME()+" checkUpdate Error : "+e.getMessage());
			return false;
		}
		finally{
			DBClose.dbClose(null, null, rs);
		}
	}
	
}
