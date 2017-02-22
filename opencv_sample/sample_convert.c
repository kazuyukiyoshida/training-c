#include<stdio.h>
#include<opencv/cv.h>
#include<opencv/highgui.h>

int main(int argc, char **argv)
{
  int i;
  CvCapture *capture;
  IplImage *src_img, *dst_img, *dst_img2;

  //CvCapture構造体の初期化、引数で使用するカメラを指定する。
  capture = cvCreateCameraCapture(atoi(argv[1]));
  //カメラからの入力画素数の設定。
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);

  //カメラからのキャプチャが失敗した場合はエラー終了
  for(i=0; i<20 ;i++){
    if((src_img = cvQueryFrame (capture)) == NULL){
      printf("camera_error\n");
      return -1;
    }
  }

  //8bit,1chの画像領域を生成
  dst_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);
  dst_img2 = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);

  //グレースケールへ変換
  cvCvtColor(src_img, dst_img, CV_BGR2GRAY);

  //エッジ画像へ変換
  cvCanny(dst_img, dst_img2, 50.0, 200.0, 3);

  //作成した画像の保存
  cvSaveImage("src_img.bmp", src_img, NULL);
  cvSaveImage("dst_img.bmp", dst_img, NULL);
  cvSaveImage("dst_img2.bmp", dst_img2, NULL);

  //終了処理
  cvReleaseCapture(&capture);
  cvReleaseImage(&dst_img);
  cvReleaseImage(&dst_img2);

  return 0;
}
