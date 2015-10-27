package Schedule;

import java.util.ArrayList;

import org.quartz.CronScheduleBuilder;
import org.quartz.JobBuilder;
import org.quartz.JobDetail;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.Trigger;
import org.quartz.TriggerBuilder;
import org.quartz.impl.StdSchedulerFactory;

public class QuatrzCreate {

	public void startJob(ArrayList<Class> arrayList, String[] timer){
		final int arrayLength=arrayList.size();
		JobBuilder jobBuilder[]=new JobBuilder[arrayLength];
		JobDetail jobDetail[]=new JobDetail[arrayLength];
		for(int i=0;i<arrayLength;i++){
			jobDetail[i]=jobBuilder[i].newJob(arrayList.get(i)).withIdentity("JOB_"+i, "GROUP_"+i).build();
			System.out.println("JOB_"+i+" : "+arrayList.get(i).toString());
		}
		
		TriggerBuilder triggerBuilder[]=new TriggerBuilder[arrayLength];
		Trigger trigger[]=new Trigger[arrayLength];
		for(int i=0;i<arrayLength;i++){
			//�� �� �� �� �� ���� �⵵(�ɼ�)
			trigger[i]=triggerBuilder[i].newTrigger().withIdentity("TRIGGER_"+i, "TRIGGER_GROUP_"+i)
					.withSchedule(CronScheduleBuilder.cronSchedule(timer[i])).build();
			//0 0 2 * * ? -> ���� ���� 2��
			//0/10 * * * * ? -> 1�ʸ���
			System.out.println("TRIGGER_"+i+" : "+arrayList.get(i).toString());
		}
		
		try {
			ArrayList<Scheduler> schArray=new ArrayList<Scheduler>();
			for(int i=0;i<arrayLength;i++) schArray.add(new StdSchedulerFactory().getScheduler());
			
			for(int i=0;i<arrayLength;i++){
				System.out.println(i);
				schArray.get(i).scheduleJob(jobDetail[i],trigger[i]);
				schArray.get(i).start();
			}	
		} catch (SchedulerException e) {
			System.out.println("QuartzMain Error : "+e.getMessage());
		}
	}

}
