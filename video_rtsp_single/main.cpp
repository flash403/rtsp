#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    // 创建RTSP服务器实例
    GstRTSPServer *server = gst_rtsp_server_new();
    // 设置监听端口为8554
    gst_rtsp_server_set_service(server, "8554");

    // 获取挂载点集合
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);

    // 创建一个媒体工厂
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

    // 设置推流管道(launch语法)
    // 用v4l2src读取摄像头，已经是h264格式，打包成RTP包
    
   gst_rtsp_media_factory_set_launch(factory,
    "( v4l2src device=/dev/video2 do-timestamp=true !\
       video/x-h264,width=1280,height=720,framerate=30/1 ! \
       queue ! rtph264pay config-interval=1 pt=96 name=pay0 )");


    
    // 设置共享管道（多客户端可用）
    gst_rtsp_media_factory_set_shared(factory, TRUE);

    // 挂载路径为/test
    gst_rtsp_mount_points_add_factory(mounts, "/test", factory);

    // 释放引用
    g_object_unref(mounts);

    // 启动RTSP服务器
    gst_rtsp_server_attach(server, NULL);

    g_print("RTSP server is running at rtsp://127.0.0.1:8554/test\n");

    // 主循环
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    // 释放资源
    g_main_loop_unref(loop);
    g_object_unref(server);

    return 0;
}

