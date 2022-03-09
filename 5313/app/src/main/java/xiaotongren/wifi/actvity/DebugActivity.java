package xiaotongren.wifi.actvity;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.InputType;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import xiaotongren.wifi.R;
import xiaotongren.wifi.common.UdpConnection_Class;


public class DebugActivity extends AppCompatActivity implements View.OnClickListener {

    private static  final  boolean IsDebug = true ;
    private static final String TAG = "DebugActivity";

    UdpConnection_Class udpConnection ;


    Button button_udp_send ;
    EditText editText_udp_send_ip;
    EditText editText_udp_send_port;
    EditText editText_udp_send;

    TextView textView_udp_send;

    EditText editText_udp_receive_port;
    Switch switch_is_receive;
    TextView textView_udp_receive;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_debug);
        setTitle("通讯调试");


        udpConnection=new UdpConnection_Class(myhandler);


        button_udp_send =(Button)findViewById(R.id.button_udp_send);
        editText_udp_send_ip=(EditText)findViewById(R.id.edittext_udp_send_ip);
        editText_udp_send_port=(EditText)findViewById(R.id.edittext_udp_send_port);
        editText_udp_send=(EditText) findViewById(R.id.edittext_udp_send);

        textView_udp_send=(TextView)findViewById(R.id.textView_udp_send);

        editText_udp_receive_port=(EditText) findViewById(R.id.edittext_udp_receive_port);
        switch_is_receive=(Switch)findViewById(R.id.switch_is_receive);
        textView_udp_receive=(TextView)findViewById(R.id.textView_udp_receive);


        button_udp_send.setOnClickListener(this);


        switch_is_receive.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener(){

            public void onCheckedChanged(CompoundButton buttonView,boolean isChecked) {
                if (isChecked) {
                    // 开启switch，设置提示信息


                    editText_udp_receive_port.setInputType(InputType.TYPE_NULL);


                    int recv_port ;

                    try {
                        recv_port=Integer.valueOf(editText_udp_receive_port.getText().toString().trim());
                        if(recv_port<1)
                        {
                            Toast.makeText(getApplicationContext(),"接收端口为大于 1 的整数", Toast.LENGTH_LONG).show();

                        }
                        else {
                            udpConnection.start(recv_port);
                        }
                    }
                    catch (Exception e)
                    {
                        Toast.makeText(getApplicationContext(),"请检查接收端口", Toast.LENGTH_LONG).show();
                    }



                } else {
                    // 关闭swtich，设置提示信息


                    editText_udp_receive_port.setInputType(InputType.TYPE_CLASS_TEXT);

//                    Toast.makeText(getApplicationContext(),"switch is closed", Toast.LENGTH_SHORT).show();

                    udpConnection.stop();



                }
            }
        });
    }


    // 此Handler处理BluetoothService传来的消息
    private final Handler myhandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case UdpConnection_Class.UDP_STATE :

                    if(IsDebug) Log.i(TAG, "MESSAGE_STATE_CHANGE: " + msg.arg1);
                    switch (msg.arg1) {
                        case UdpConnection_Class.UDP_STATE_CONNECT_OK:
                            setTitle("通讯连接成功");
                            break;
                        case UdpConnection_Class.UDP_STATE_CONNECT_FAIL:
                            setTitle("通讯连接失败");
                            break;
                        case UdpConnection_Class.UDP_STATE_DISCONNECT_OK:
                            setTitle("通讯连接已断开");
                            break;
                        case UdpConnection_Class.UDP_STATE_DISCONNECT_FAIL:
                            setTitle("通讯连接断开失败");
                            break;
                    }

                    break;
                case UdpConnection_Class.UDP_STATE_WRITE:
                    byte[] writeBuf = (byte[]) msg.obj;
                    int send_len = msg.arg1;

                    UDP_writeCallback(writeBuf,send_len);
                    break;
                case UdpConnection_Class.UDP_STATE_READ:
                    //String readMessage = (String) msg.obj;
                    // 读取到的数据
                    //reveiveMessage(readMessage);

                    byte[] recv_buf_local = (byte[])msg.obj;
                    int len = msg.arg1;
                    UDP_reveiveMessage(recv_buf_local,len);

                    break;

            }
        }
    };


    private void UDP_reveiveMessage(byte[] buf,int len)
    {


        String show_str = textView_udp_receive.getText()+ new String(buf,0,len);
        textView_udp_receive.setText(show_str);

    }


    private void UDP_writeCallback(byte[] buf,int len)
    {

        String show_str = textView_udp_send.getText()+ new String(buf,0,len);
        textView_udp_send.setText(show_str);

    }





    @Override
    public void onClick(View view)
    {
        switch (view.getId())
        {

            case R.id.button_udp_send:


                int send_port ;
                String send_ip = editText_udp_send_ip.getText().toString().trim();
                String send_str = editText_udp_send.getText().toString().trim();

                try {
                    send_port=Integer.valueOf(editText_udp_send_port.getText().toString().trim());
                    if(send_port<1)
                    {
                        Toast.makeText(getApplicationContext(),"发送端口为大于 1 的整数", Toast.LENGTH_LONG).show();
                        break;
                    }
                }
                catch (Exception e)
                {
                    Toast.makeText(getApplicationContext(),"请检查发送端口", Toast.LENGTH_LONG).show();
                    break;
                }

                udpConnection.write(send_str.getBytes(),send_ip,send_port);


        }

    }


    @Override
    protected void onStop() {

        if(udpConnection.getState()==UdpConnection_Class.UDP_STATE_CONNECT_OK)
        {
            udpConnection.stop();
        }
        super.onStop();
    }

    @Override
    public void onBackPressed() {
        if(udpConnection.getState()==UdpConnection_Class.UDP_STATE_CONNECT_OK)
        {
            udpConnection.stop();
        }
        super.onBackPressed();
    }

    @Override
    protected void onDestroy() {

        if(udpConnection.getState()==UdpConnection_Class.UDP_STATE_CONNECT_OK)
        {
            udpConnection.stop();
        }
        super.onDestroy();
    }
}
