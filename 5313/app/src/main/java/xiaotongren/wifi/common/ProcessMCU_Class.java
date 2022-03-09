package xiaotongren.wifi.common;

import android.util.Log;



    public class ProcessMCU_Class {





        //串口解析变量
        public static final char Uart_Pack_property_head  = 0xFF ;
        public static final char Uart_Pack_property_tail  = 0XFE ;
        public static final char parse_recv_buff_pack_len  = 100 ;

        char[] recv_buff_pack = new char[parse_recv_buff_pack_len];
        private int recv_flag_recv_point = 0 ;
        private boolean recv_flag_recv_star = false ;
        private boolean recv_flag_recv_stop = false ;
        private char recv_flag_recv_last = 0;


        public  char c_char_to_java_char(byte num)
        {
            if(num<0)
            {
                return (char)(256+num);
            }
            else {
                return (char)num;
            }
        }


        public static byte java_char_to_c_char(char num)
        {
            if(num>=0)
            {
                if(num<1)
                {
                    return (byte)(256+num);
                }
                else {
                    return (byte)num;
                }
            }
            return 0;
        }




        public  void process_data_from_mcu(ProcessMCU_Interface date_process, byte[] buf)
        {

            Log.e("proceess_date","coming  coming");
            char recv_buff[] = new char[buf.length];
            for(int i=0;i<buf.length;i++)
            {
                recv_buff[i]=c_char_to_java_char(buf[i]);
            }

            for (char one_buf : recv_buff) {
                if (one_buf == Uart_Pack_property_head && recv_flag_recv_last == Uart_Pack_property_head) {
                    recv_flag_recv_star = true ;
                    recv_flag_recv_stop = false ;
                    recv_flag_recv_point = 0 ;
                } else if (one_buf == Uart_Pack_property_tail  && recv_flag_recv_last == Uart_Pack_property_tail ) {
                    if (recv_flag_recv_star) {

                        if (recv_flag_recv_point > 0 && recv_flag_recv_point > recv_buff_pack[0]) {
                            if (recv_flag_recv_point-1 == recv_buff_pack[0]) {

                                /****************用户处理区********************/


                                char[] send_buff = new char[recv_flag_recv_point-1];
                                for (int i=0 ;i<recv_flag_recv_point-1;i++)
                                {
                                    send_buff[i]= recv_buff_pack[i+1];
                                }

                                date_process.processMCU_callback((int)recv_buff_pack[0]-1,send_buff);


                                /****************用户处理区********************/

                                //接收完毕
                                recv_flag_recv_star = false;
                                recv_flag_recv_stop = true ;
                                recv_flag_recv_point = 0 ;

                            } else {
                                //接收出错，接收长度于实际长度不符,重新开始
                                recv_flag_recv_point = 0 ;
                                recv_flag_recv_star = false ;
                                recv_flag_recv_stop = false ;
                                //memset(recv_buff_pack, 0, parse_recv_buff_pack_len);

                            }
                        } else {
                            //接收出错，接收长度于实际长度不符,重新开始
                            recv_flag_recv_point = 0 ;
                            recv_flag_recv_star = false ;
                            recv_flag_recv_stop = false ;
                        }
                    }
                } else {
                    if (recv_flag_recv_star) {
                        if (recv_flag_recv_point > (parse_recv_buff_pack_len - 1) ) {
                            //如果数据越界，直接清零,重新开始
                            recv_flag_recv_point = 0 ;
                            recv_flag_recv_star = false ;
                            recv_flag_recv_stop = false ;
                            //memset(recv_buff_pack, 0, parse_recv_buff_pack_len);
                        } else {
                            //保存接收数据
                            recv_buff_pack[recv_flag_recv_point] = one_buf;
                            recv_flag_recv_point++;
                        }
                    }
                }
                recv_flag_recv_last = one_buf;  //添加历史记录
            }

        }

    }
