package xiaotongren.wifi.common;

/**
 * Created by Administrator on 2017/2/4.
 */

public interface ProcessMCU_Interface {

   //public void processMCU_callback(char cmd ,char value);
   public  void processMCU_callback(int len, char[] value);
  // public void processMCU_callback(byte cmd ,byte value);
  // public void processMCU_callback(byte cmd ,byte[] value);

}
