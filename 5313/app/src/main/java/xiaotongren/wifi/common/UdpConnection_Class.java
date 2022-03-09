package xiaotongren.wifi.common;

import android.os.Handler;
import android.util.Log;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;


/**
 * Created by Administrator on 2017/2/6.
 */

public class UdpConnection_Class {

    private static final String TAG = "UDPSocketClient";
    private static final boolean IsDebug = false;

    private  DatagramSocket mysocket;
    private  Handler myhandler ;
    private AcceptThread myAcceptThread;
    private SendThread mySendThread;

    private int connection_State = UDP_STATE_CONNECT_NONE; //保存连接状态



    //发送处理程序的消息类型及状态

    public static final int UDP_STATE = 100;
    public static final int UDP_STATE_CONNECT_FAIL = 1;
    public static final int UDP_STATE_CONNECT_OK = 2;
    public static final int UDP_STATE_DISCONNECT_OK = 3;
    public static final int UDP_STATE_DISCONNECT_FAIL = 4;
    public static final int UDP_STATE_CONNECT_NONE = 5;

    public static final int UDP_STATE_READ = 13;
    public static final int UDP_STATE_WRITE = 14;
    public static final int UDP_STATE_READ_FAIL = 15;
    public static final int UDP_STATE_WRITE_FAIL = 16;



    //最大缓冲数据
    public static final int RECEIVE_BUFF_MAX_LEN = 256;

    //默认端口
    public int UDP_DEFAULT_PORT = 8080;


    public UdpConnection_Class(Handler handler) {

        this.myhandler = handler;


    }



    /**
     * 设置当前的连接状态
     * @param state  连接状态
     */
    private synchronized void set_connection_State(int state) {
        if (IsDebug) Log.d(TAG, "set_connection_State() " + connection_State + " -> " + state);
        connection_State = state;
        // 通知Activity更新UI
        myhandler.obtainMessage(UDP_STATE, state, -1).sendToTarget();
    }

    private synchronized void set_IO_State(int state) {
        if (IsDebug) Log.d(TAG, "set_connection_State() " + connection_State + " -> " + state);
        // 通知Activity更新UI
        myhandler.obtainMessage(UDP_STATE, state, -1).sendToTarget();
    }



    public synchronized void start(int port)
    {
        try {

            this.mysocket = new DatagramSocket(port);

            set_connection_State(UDP_STATE_CONNECT_OK);

            if (IsDebug) Log.e(TAG, "UDP  start");

        } catch (SocketException e) {

            set_connection_State(UDP_STATE_CONNECT_FAIL);

            if (IsDebug) {
                Log.e(TAG, "SocketException");
            }
            return;
        }

        //if (myAcceptThread != null) {myAcceptThread.cancel(); myAcceptThread = null;}

        myAcceptThread = new AcceptThread();
        myAcceptThread.start();

    }


    /**
     * close the UDP socket
     */
    public  void stop() {


        try{
            myAcceptThread.cancel();
            this.mysocket.close();
            set_connection_State(UDP_STATE_DISCONNECT_OK);
            Log.e(TAG, "udp  stop");
        }catch (Exception e)
        {
            set_connection_State(UDP_STATE_DISCONNECT_FAIL);

        }
    }


    public  int getState() {
        return connection_State;
    }


    synchronized public void write(byte[] data,String targetHostName ,int targetPort)
    {
        if(connection_State==UDP_STATE_CONNECT_OK)
        {
            try
            {
                mySendThread=new SendThread(data,targetHostName,targetPort);
                mySendThread.start();
            }
            catch (Exception e)
            {

            }
        }
    }


    synchronized public void write(char[] data,String targetHostName ,int targetPort)
    {
        int i = 0;
        byte[] send_buff = new byte[data.length];
        for(i=0;i<data.length;i++)
        {
            send_buff[i] = ProcessMCU_Class.java_char_to_c_char(data[i]);
        }

        write(send_buff,targetHostName ,targetPort);
    }





    private class AcceptThread extends Thread {

        private boolean is_run = true ;

        int read_fail_times = 0;

        public void run() {

            while (is_run)
            {
                while(connection_State==UDP_STATE_CONNECT_OK)
                {

                    if (IsDebug) Log.d(TAG, "start read");

                    byte[] buff_recv = new byte[RECEIVE_BUFF_MAX_LEN];
                    DatagramPacket packet=new DatagramPacket(buff_recv, RECEIVE_BUFF_MAX_LEN);

                    try{
                        mysocket.receive(packet);

//                    int len = packet.getLength();
//
//                    byte[] send_buff = new byte[len];
//                    System.arraycopy(packet.getData(),0,send_buff,0,len);

                        if (IsDebug) Log.d(TAG, "UDP  read");

                        myhandler.obtainMessage(UDP_STATE_READ, packet.getLength(), -1, packet.getData())
                                .sendToTarget();

                        read_fail_times= 0 ;

                    }catch (IOException e)
                    {
                        if(connection_State==UDP_STATE_CONNECT_OK)
                        {
                            set_connection_State(UDP_STATE_READ_FAIL);
                            read_fail_times++;
                            if(IsDebug) Log.e(TAG, "read data: IOException:"+e.toString());
                        }
                    }

            }

            }
        }

        public void cancel() {
            this.is_run = false ;
        }

    }

    private class SendThread extends Thread {
        byte data[];
        String targetHostName;
        int targetPort;

        public SendThread(byte[] data,String targetHostName ,int targetPort)
        {
            this.data = data;
            this.targetHostName =targetHostName;
            this.targetPort=targetPort;
        }


        public void run() {

            try {
                DatagramPacket localDatagramPacket = new DatagramPacket(
                        data, data.length,
                        InetAddress.getByName(targetHostName), targetPort);
                try{
                    mysocket.send(localDatagramPacket);

                    myhandler.obtainMessage(UDP_STATE_WRITE, data.length, -1,data)
                            .sendToTarget();

                    if (IsDebug) Log.e(TAG, "UDP  send ok ");
                }
                catch (Exception e)
                {
                    if (IsDebug) Log.e(TAG, "UDP  write fail"+e.toString());
                }
                
                if (IsDebug) Log.e(TAG, "UDP  write");

            }catch (IOException e) {

                set_IO_State(UDP_STATE_WRITE_FAIL);

                if (IsDebug) Log.e(TAG, "sendData(): IOException, but just ignore it");

            }

        }

    }






}
