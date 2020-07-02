
import java.util.concurrent.*;
import java.util.Arrays;
import java.util.List;
import java.io.*;
public class mergesort extends RecursiveAction
{
    static final int MAX_SIZE = 10000;
    static final int THRESHOLD = 100;
    static final int MAX_NUM = 100000;

    private int begin;
    private int end;
    private int[] array;
    private int[] tmparray;

    public mergesort(int begin, int end, int[] array,int []tmparray) {
        this.begin = begin;
        this.end = end;
        this.array = array;
	this.tmparray=tmparray;
    }

    protected void compute() {
        if (end - begin < THRESHOLD) {
            // conquer stage 
            for(int lh=begin;lh<=end-1;++lh)
		        for(int rh=lh+1;rh<=end;++rh)
			        if(array[rh]<array[lh])
			            {int tmp=array[lh];array[lh]=array[rh];array[rh]=tmp;}
	return;
        }
        else {
            int mid=(begin+end)/2;
	invokeAll(new mergesort(begin, mid, array,tmparray),new mergesort(mid+1, end, array,tmparray));
	int i=begin,j=mid+1;
	int k=begin;
	while(i<=mid&&j<=end){
		if(array[i]<array[j])tmparray[k++]=array[i++];
		else tmparray[k++]=array[j++];
	}
	while(i<=mid)tmparray[k++]=array[i++];
	while(j<=end)tmparray[k++]=array[j++];
        }
    }

	public static void main(String[] args) {
		ForkJoinPool pool = new ForkJoinPool();
        	int nowsize;
		
		// create SIZE random integers between 0 and 9
		java.util.Random rand = new java.util.Random();
        nowsize=rand.nextInt(MAX_SIZE);
        int []array = new int[nowsize];
	int []tmparray=new int[nowsize];
		for (int i = 0; i < nowsize; i++) {
			array[i] = rand.nextInt(MAX_NUM);
		}		
		
        //write to qsort1.txt
         try { 
            File writename = new File("msort1.txt"); // 相对路径，如果没有则要建立一个新的output。txt文件  
            writename.createNewFile();
		    StringBuilder sb = new StringBuilder();
		    for(int i = 0; i < nowsize; i++){
		            sb.append(array[i]).append("\n");
		    }
		    sb.deleteCharAt(sb.length() -1);
                BufferedWriter out = new BufferedWriter(new FileWriter(writename));  
                out.write(sb.toString());//  
                out.flush(); // 把缓存区内容压入文件  
                out.close(); // 最后记得关闭文件  
      
            } catch (Exception e) {  
                e.printStackTrace();  
            }  




		mergesort task = new mergesort(0, nowsize-1, array,tmparray);

		pool.invoke(task);

        //write the result
        try { 
            File writename = new File("msort2.txt"); 
            writename.createNewFile();
		    StringBuilder sb = new StringBuilder();
		    for(int i = 0; i < nowsize; i++){
		            sb.append(tmparray[i]).append("\n");
		    }
		    sb.deleteCharAt(sb.length() -1);
                BufferedWriter out = new BufferedWriter(new FileWriter(writename));  
                out.write(sb.toString());//  
                out.flush(); // 把缓存区内容压入文件  
                out.close(); // 最后记得关闭文件  
      
            } catch (Exception e) {  
                e.printStackTrace();  
            }  



		System.out.println("Mergesort\nNumber: "+nowsize);
	}
}


