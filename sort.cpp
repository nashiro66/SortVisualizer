#include "sort.h"
#include "mainwindow.h"
#define INFTY 1000000001


Sort::Sort(int num,QGraphicsScene * animationScene,QGraphicsView * animationView,int speed){
    sort_num=num;
    ok=true;
    m_scene=animationScene;
    m_view=animationView;
    width=std::max(512/sort_num,1);
    m_speed=speed;
}

Sort::~Sort(){
    m_scene->clear();
    m_view->viewport()->update();
}

void Sort::Stop(bool running){
    running_now=running;
    while(!running_now){
     QApplication::processEvents();
    }
}

//時間を遅らせる
void Sort::delay(){
    QEventLoop loop;
    QTimer::singleShot(5*m_speed*m_speed, &loop, SLOT(quit()));
    loop.exec();
}

//generateしたものを描画
void Sort::draw(){
    if(drawn){
        m_scene->clear();
    }
    //描画
    QPen pen = QPen (ORANGE) ;
    QBrush brush = QBrush (ORANGE) ;
    for(int i=0;i<sort_num;i++){
            rects.push_back(m_scene->addRect(i*width,0,width,-vec[i]*2,pen,brush));
    }
    drawn=1;
}


//Sort中に色を変える
void Sort::render(int i,QColor C){
    QPen pen = QPen (C) ;
    QBrush brush = QBrush (C) ;
    rects[i]->setPen(pen);
    rects[i]->setBrush(brush);
    rects[i]->setRect(QRect(i*width,0,width,-vec[i]*2));
    m_view->viewport()->update();
}


//昇順
void Sort::Ascending(){
    for(int i=0;i<sort_num;i++){
        vec.append((i)*255/(sort_num-1));
    }
    draw();
}

//降順
void Sort::Descending(){
    for(int i=sort_num-1;i>=0;i--){
        vec.append((i)*255/(sort_num-1));
    }
    draw();
}

//ランダム
void Sort::random(){
    // initialize random generator
    qsrand( QTime::currentTime().msec() );
    for(int i=0;i<sort_num;i++){
        int random = qrand() % (256);
        //add random number
        vec.append(random);
    }
    draw();
}

//sort中の入れ替え
void Sort::swap(int i,int k){
    int temp;
    temp=vec[k];
    vec[k]=vec[i];
    vec[i]=temp;
    //swap中の箇所の色を紫にする
    render(k,PURPLE);
    render(i,PURPLE);
    delay();
    //swap中の箇所の色をオレンジに戻す
    render(k,ORANGE);
    render(i,ORANGE);
}

//バブルソート
void Sort::Bubble(){
    for(int i=0;i<sort_num;i++){
        for(int j=sort_num-1;j>i;j--){
            if(vec[j-1]>vec[j]){
                swap(j-1,j);
            }
        }
        //Sort済の色を変える
        render(i,GREEN);
    }
}

//挿入ソート
void Sort::Insert(){
    for(int i=1;i<sort_num;i++){
        int j=i;
        delay();
        //ソート済あるいはjが0のときはループから外れる
        while((j>0)&&(vec[j-1]>vec[j])){
            swap(j-1,j);
            //並び替え終わったj番目を緑にする
            render(j,GREEN);
            //更新
            j--;
        }
        //順番に並んでいるj番目を緑にする
        render(j,GREEN);
    }
}

//シェルソート
void Sort::Shell(){
    int k=1;
    while(k<sort_num){
        k*=2;
    }
    while(k>0){
        for(int i=k;i<sort_num;i++){
            for(int j=i;j>=k;j-=k){
                if(vec[j]<vec[j-k]){
                    swap(j,j-k);
                }
            }
        }
        k/=2;
    }
    //ソート済箇所を緑にする
    for(int i=0;i<sort_num;i++){
        render(i,GREEN);
    }
}


//クイックソート
void Sort::Quick_middle(int left_ini,int right_ini){
    int left=left_ini;
    int right=right_ini;

    //軸は真ん中
    int middle=(left+right)/2;
    int middle_num=vec[middle];

    while(1){
        //middle_numより小さい値を左から見つけていく
        while(vec[left]<middle_num){left++;}
        //middle_numより大きい値を右から見つけていく
        while(vec[right]>middle_num){right--;}
        //leftがrightより大きければ終わり
        if(left>=right) {break;}

        swap(left,right);
        //更新
        left++;
        right--;
    }

    //leftとrightが同じときはsort済みなので緑にする
    if(left==right){
        render(left,GREEN);
    }

    //分割したものをさらにクイックソートしていく
    //左側
    if(left_ini<left-1)
    {
        Quick_middle(left_ini,left-1);
    }
    //sortし終わった部分を緑にする
    else if(left_ini+1==left){
        render(left_ini,GREEN);
        render(left_ini+1,GREEN);
    }
    else if(left_ini==left){
        render(left_ini,GREEN);
    }

    //右側
    if(right+1<right_ini)
    {
        Quick_middle(right+1,right_ini);
    }
    //sortし終わった部分を緑にする
    else if(right+1==right_ini){
        render(right_ini-1,GREEN);
        render(right_ini,GREEN);
    }
    else if(right==right_ini){
        render(right_ini,GREEN);
    }
}

void Sort::Quick(){
    Quick_middle(0,sort_num-1);
}


void Sort::Heap(){
    //ヒープ構造(親が左右の子より大きい)にしていく
    for(int i=(sort_num-2)/2;i>=0;i--){
        downHeap(i,sort_num-1);
    }

    for(int i=sort_num-1;i>0;i--){
        //根と配列の末尾を入れ替える
        swap(0,i);
        //i番目は一番後ろのまま、入れ替えた根を適切な位置へ移動する
        downHeap(0,i-1);
        //末尾はソート完了で緑にする
        render(i,GREEN);
    }
    //最後の要素も色を変える
    render(0,GREEN);
}

void Sort::downHeap(int i,int k){
    //親の値を取っておく
    while(1){
        //子にたどり着く
        int j=2*i+1;
        //子が要素数より大きければループを抜ける
        if(j>k) break;
        //要素数よりjが小さい限り
        if(j!=k){
            //右の子が左の子より大きければ右の子に移動する
            if(vec[j+1]>vec[j]){
                j++;
            }
        }
        //親が子より大きければループを抜ける
        if(vec[i]>vec[j]) break;

        //親と子を入れ替える
        swap(i,j);
        //親を子に更新
        i=j;
    }
}

void Sort::MergeSort(){
    MergeSplit(0,sort_num);
    for(int i=0;i<sort_num;i++){
        render(i,GREEN);
    }
}

void Sort::Merge(int left,int mid,int right){
    QVector<int> tmp_left;
    QVector<int> tmp_right;

    //左部分の配列をコピー
    for(int i=0;i<(mid-left);i++){
        tmp_left.append(vec[left+i]);
    }
    //右部分の配列をコピー
    for(int i=0;i<(right-mid);i++){
        tmp_right.append(vec[mid+i]);

    }

    //末尾に無限を代入することで以降の比較を楽にする
    tmp_left.append(INFTY);
    tmp_right.append(INFTY);

    //sortする
    int j=0;
    int k=0;
    for(int i=left;i<right;i++){
        if(tmp_left[j]<=tmp_right[k]){
            vec[i]=tmp_left[j];
            j++;
        }else{
            vec[i]=tmp_right[k];
            k++;
        }
        //ソートし終わった部分を緑にする
        render(i,GREEN);
        delay();
    }
}

void Sort::MergeSplit(int left,int right){
    //分割が一つになった場合は何もしない
    if(right>left+1){
        //左右に分割していく(末尾の要素の配列は存在しないことに注意)
        int middle=(left+right)/2;
        MergeSplit(left,middle);
        MergeSplit(middle,right);

        //結合していく
        Merge(left,middle,right);
    }
}
