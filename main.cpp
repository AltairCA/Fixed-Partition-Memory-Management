//IT14022470
//Batch 02
//M.M.I.Perera
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QProcess>
#include <iomanip>
using namespace std;
void returntime_msg(int size_of_array,int element_time1[],int storage_count,int min_array[],int &min_array_time,QString msg[],bool is_msg){


    int process_re[size_of_array];
    int element_time[size_of_array];
    // int min_array[size_of_array];
    //copy elements to the new arrays
    for(int x=1;x<=size_of_array;x++){
        process_re[x-1]=x;
        element_time[x-1] = element_time1[x-1];
        //  min_array[x-1] = min_array1[x-1];
    }
    //sorting to new arrays before calculate the turn around time because smallest time operation need to be allocate first
    int min_index = 0;
    for(int x=0;x<size_of_array;x++){
        min_index=x;
        for(int y=x;y<size_of_array;y++){
            if(element_time[min_index]>element_time[y]){
                min_index = y;
            }
        }
        int t= element_time[min_index];
        element_time[min_index] = element_time[x];
        element_time[x] = t;
        t = process_re[min_index];
        process_re[min_index] = process_re[x];
        process_re[x] = t;
        //process_re[x]=min_index + 1;
    }

    //for(int x=0;x<size_of_array;x++){
    //    qDebug()<<QString::number(element_time[x]);
    //}



    int count = 0;
    int temp[size_of_array];


    min_array_time = 0;
    for(int x=1;x<=storage_count;x++){
        count = 0;

        for(int y=0;y<size_of_array;y++){
            // store what are the processors runs in each storage ,the processors are store in temp
            if(min_array[y] == x){
                temp[count] = y+1;

                count++;
            }

        }
        int previous_time =0;
        if(is_msg){
            for(int z=0;z<size_of_array;z++){
                for(int a=0;a<count;a++){
                    //process_re has the process numbers sorted according to the time
                    if(temp[a]==process_re[z]){
                        // qDebug()<<QString::number(temp[a]);
                        msg[process_re[z]-1] = "Program "+QString::number(process_re[z])+" runs in region "+QString::number(x)+" from "+QString::number(previous_time)+" to ";
                        previous_time = previous_time + element_time[z];
                        min_array_time = min_array_time + previous_time;
                        msg[process_re[z]-1] = msg[process_re[z]-1] + QString::number(previous_time);
                    }
                }
            }
        }else{
            for(int z=0;z<size_of_array;z++){
                for(int a=0;a<count;a++){
                    if(temp[a]==process_re[z]){
                        // qDebug()<<QString::number(temp[a]);
                        //msg[process_re[z]-1] = "Program "+QString::number(process_re[z])+" runs in region "+QString::number(x)+" from "+QString::number(previous_time)+" to ";
                        previous_time = previous_time + element_time[z];
                        min_array_time = min_array_time + previous_time;
                        //msg[process_re[z]-1] = msg[process_re[z]-1] + QString::number(previous_time);
                    }
                }
            }
        }

    }


}

int calc_time(int arr[],int size_of_elemetns[],int element_count,int element_time[],int storage_details[],int storage_count){


    for(int x=0;x<element_count;x++){
        if(storage_details[arr[x]-1]>=size_of_elemetns[x]){
            //check for validitiy arr = 1221
            //storage walata danna puluwanda kiyala check karanawa


        }else{

            return -1;
        }
        
    }

    int turnaround_time = 0;

    //QString msg[element_count];
    returntime_msg(element_count,element_time,storage_count,arr,turnaround_time,NULL,false);
    return turnaround_time;
}

void rec(int arr[],int size_of_elemetns[],int element_count,int storage_count,int point, int element_time[],int storage_details[],int min_array[],int &min_array_time){
    //arr hold the current combination
    arr[point] = 0;

    QString temp = "";

    for(int x = 0; x< storage_count;x++){



        arr[point] = arr[point]+1;

        //generating the combinations
        if(point != element_count-1){
            rec(arr,size_of_elemetns,element_count,storage_count,point+1,element_time,storage_details,min_array,min_array_time);
        }else{



            //calculate the turnaround time
            int asd = calc_time(arr,size_of_elemetns,element_count,element_time,storage_details,storage_count);
            //check for the returend turnaround time is less than the current minimum turnaround time if
            //its save the current combination in min_array
            if(asd<min_array_time && asd!=-1){
                //qDebug()<<QString::number(asd);

                min_array_time = asd;

                //the combinations output

                // temp = "";
                for(int y=0;y<element_count;y++){
                    //   temp = temp + QString::number(arr[y]);
                    //current minimum
                    min_array[y] = arr[y];
                }


                // qDebug()<<temp;



            }
        }






    }

}

int main(int argc, char *argv[])
{
    int cases = 1;
    char input[100];
    while(true){
        try{



            int storage_count=2;
            int size_of_array=4;
            //qDebug()<<"hello";
            cout<<"Enter the frist parameter : ";

            cin>>input;
            storage_count = atoi(input);
            //cout<<"Storage count : "<<storage_count<<endl;
            cin>>input;
            size_of_array = atoi(input);
            //cout<<"Input size : "<<size_of_array<<endl;

            cout<<"Enter the Second parameters : ";
            int storage_details[storage_count];
            for(int x=0;x<storage_count;x++){
                cin>>input;
                storage_details[x] = atoi(input);
            }
            // int storage_details[storage_count]={40,60};
            cout<<"Enter the Inputs"<<endl;
            int arry[size_of_array];
            int size_of_elements[size_of_array];
            int element_time[size_of_array];
            int min_array[size_of_array];
            for(int x=0;x<size_of_array;x++){
                cout<<endl<<"Enter the "<<(x+1)<<" input : ";

                cin>>input;
                int z = atoi(input);
                cin>>input;
                int size_min  = atoi(input);
                cin>>input;
                int time_min = atoi(input);
                for(int y=1;y<z;y++){
                    cin>>input;
                    int temp1 = atoi(input);
                    cin>>input;
                    int temp2 = atoi(input);;
                    if(time_min>temp2){
                        size_min  = temp1;

                        time_min = temp2;
                    }
                }
                size_of_elements[x] = size_min;
                element_time[x] = time_min;
                min_array[x]=1;

            }

            // int size_of_elements[size_of_array]={35,20,40,60};
            //  int element_time[size_of_array]={4,3,10,7};
            //int min_array[size_of_array]={1,1,1,1,};
            int min_array_time=INT_MAX; // 4+3+10+7






            //int total_time_foreach_storage[storage_count]; // assing 0 by for loop
            rec(arry,size_of_elements,size_of_array,storage_count,0,element_time,storage_details,min_array,min_array_time);


            int returntime;
            QString msg[size_of_array];
            returntime_msg(size_of_array,element_time,storage_count,min_array,returntime,msg,true);
            cout<<endl;
            cout<<"Case "<<cases<<endl;
            cout<<std::fixed<<setprecision( 2 )<<"Average turnaround time = "<<double(returntime/double(size_of_array))<<endl;
            for(int x=0;x<size_of_array;x++){
                cout << msg[x].toStdString()<<endl;

            }
        }catch(...){
            cout<<"Please check your inputs "<<endl;
        }
        cout<<endl<<"Do you want to run again (y/n) : ";

        cin>>input;
        QString string(input);
        if(string=="n"){
            exit(EXIT_SUCCESS);
            break;

        }else{
            cases++;
#ifdef Q_OS_WIN32
            system("cls");
#endif

#ifdef Q_OS_LINUX
            system("clear");
#endif
        }
    }
    QCoreApplication a(argc, argv);

    return a.exec();
}

