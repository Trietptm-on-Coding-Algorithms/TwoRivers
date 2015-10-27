package Schedule;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.quartz.JobExecutionContext;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.core.QuartzScheduler;
import org.quartz.core.QuartzSchedulerResources;
import org.quartz.impl.StdSchedulerFactory;

//�׽�Ʈ �� �غ�.
//���� ���� ���� �۾� ����Ʈ ��� �� �װ��� shutdown�ϴ� �޼ҵ�
//�ϴ� ������.
//����� �ȵ�.

public class QuartzShutdown {
	private static QuartzShutdown qs;
	private QuartzShutdown(){}
	public static synchronized QuartzShutdown getQuartzShutdown(){
		if(qs==null) qs=new QuartzShutdown();
		return qs;
	}
	
	public ArrayList<JobExecutionContext> executingQuartz(){
		Scheduler sched;
		ArrayList<JobExecutionContext> arr = null;
		try {
			sched = new StdSchedulerFactory().getScheduler();
			List jobsList = sched.getCurrentlyExecutingJobs();
			Iterator jobsIterator = jobsList.listIterator();   
			arr=new ArrayList<JobExecutionContext>();

			while(jobsIterator.hasNext())
			{
			    JobExecutionContext context = (JobExecutionContext) jobsIterator.next();
			    Date previous = context.getPreviousFireTime();
			    if (previous == null) continue; 
			    System.out.println("Fire Instance ID : "+context.getFireInstanceId());
			    arr.add(context); 
			}
		} catch (SchedulerException e) {
			System.out.println("QuartzShutdown Error : "+e.getMessage());
		}
		return arr;
	}
	
	public void shtudownQuartz(){
		ArrayList<JobExecutionContext> jArr=executingQuartz();
		for(JobExecutionContext jc:jArr){
			try {
				System.out.println(jc.getFireInstanceId());
				jc.getScheduler().shutdown();
			} catch (SchedulerException e) {
				System.out.println("QuartzShtudown shutdown Error : "+e.getMessage());
			}
		}
	}
}
