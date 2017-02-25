2/25(土)_1 吉田：
このツリーはArmadillo-810をベースにしています。

吉田環境では下記を使用(使用予定)しています。
ブートローダー：hermit-at-3.2_3.2.4.tar.gz (使う予定)
カーネル　　　：linux-3.4-at20.tar.gz
ユーザーランド：atmark-dist-20160927.tar.gz

このgitツリーを下記のフォルダ名に置き換えて使ってもいいですし、
make menu-configの対象をこのgitツリーのディレクトリ名にしてコンパイルすればOKです。
atmark-dist-20160927/vendors/AtmarkTechno/Armadillo-810

----------
2/25(土)_2 吉田：
直下に下記のサンプルを作成して置いてます。

test:
 hello worldプログラム

opencv_sample : 
 下記HPに掲載されているカメラで撮影するサンプルです。
 http://armadillo.atmark-techno.com/howto/armadillo-810-opencv

led_test:
 ５秒おきに順番にLEDを光らせ、５秒おきに順番にLEDを消すだけプログラム
 やっつけなので動いてますが、バグってるかも。。。
----------
2/25(土)_3 吉田：
 test-branchというブランチを遊びで作成しました。
 好きにコミットなどしてみていじり倒してください。

----------
