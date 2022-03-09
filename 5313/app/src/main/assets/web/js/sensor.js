//<script src="js/jquery-1.8.3.min.js"></script>

var server_url_sensor = cfg_sensor_monitor_url;
var server_url_control = cfg_sensor_control_url;

var request_period = 2000; //ms

///////////////////////////////////////////////////
var timer_request;

var flag_is_start = false;

var flag_is_delay = 0;

var recv_callback;

function monitor_sensor() {
	$.ajax({
		type: "get",
		url: server_url_sensor,
		async: true,
		dataType: "json",
		success: function(data) {

			if(flag_is_start) {
				if(flag_is_delay > 0) {
					flag_is_delay--;
				} else {
					recv_callback(data);
				}

			}
		}
	});
}

function update_control(arg_name, arg_value) {

	if(flag_is_start == true) {

		flag_is_delay = 3;

		$.get(server_url_control, {
			sensor_type: arg_name,
			sensor_value: arg_value
		});
	}
};

function start_monitor_sensor(callback_function) {
	recv_callback = callback_function;
	timer_request = setInterval("monitor_sensor();", request_period);
	flag_is_start = true;
}

function stop_monitor_sensor() {
	window.clearInterval(timer_request);
	flag_is_start = false;
}