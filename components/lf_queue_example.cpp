#include "thread_utils.h"
#include "lf_queue.h"

struct MyStruct {
    int d_[3];
};

using namespace Components;

auto consumeFunction(LFQueue<MyStruct>* lfq) {
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(5s);

    while (lfq->size()) {
        const auto d = lfq->getNextToRead();
        lfq->updateReadIndex();

        std::cout << "consumeFunction read elem: " << d->d_[0] << ", " << d->d_[1] << ", " << d->d_[2] << " lfq-size: " << lfq->size() << std::endl;

        std::this_thread::sleep_for(1s);
    }

    std::cout << "consumerFunction exiting." << std::endl;
}

int main(int, char **) {
    LFQueue<MyStruct> lfq(20);

    auto ct = createAndStartThread(-1, "", consumeFunction, &lfq);

    for (auto i = 0; i < 50; ++i) {
        const MyStruct d{i, i * 10, i * 100};
        *(lfq.getNextToWriteTo()) = d;
        lfq.updateWriteIndex();

        std::cout << "main constructed elem: " << d.d_[0] << ", " << d.d_[1] << ", " << d.d_[2] << " lfq-size: " << lfq.size() << std::endl;

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);
    }

    ct->join();

    std::cout << "main exiting." << std::endl;

    return 0;
}


/*
Set core affinity for  132877639480896 to -1
main constructed elem:0,0,0 lfq-size:1
main constructed elem:1,10,100 lfq-size:2
main constructed elem:2,20,200 lfq-size:3
main constructed elem:3,30,300 lfq-size:4
consumeFunction read elem:0,0,0 lfq-size:3
main constructed elem:4,40,400 lfq-size:4
consumeFunction read elem:1,10,100 lfq-size:3
main constructed elem:5,50,500 lfq-size:4
consumeFunction read elem:2,20,200 lfq-size:3
main constructed elem:6,60,600 lfq-size:4
consumeFunction read elem:3,30,300 lfq-size:3
main constructed elem:7,70,700 lfq-size:4
consumeFunction read elem:4,40,400 lfq-size:3
main constructed elem:8,80,800 lfq-size:4
consumeFunction read elem:main constructed elem:59,90,,90050 lfq-size:,500 lfq-size:44

main constructed elem:10,100,1000 lfq-size:5
consumeFunction read elem:6,60,600 lfq-size:4
main constructed elem:11,110,1100 lfq-size:5
consumeFunction read elem:7,70,700 lfq-size:4
main constructed elem:12,120,1200 lfq-size:5
consumeFunction read elem:8,80,800 lfq-size:4
main constructed elem:13,130,1300 lfq-size:5
consumeFunction read elem:9,90,900 lfq-size:4
main constructed elem:14,140,1400 lfq-size:4consumeFunction read elem:
10,100,1000 lfq-size:4
main constructed elem:15,150,1500 lfq-size:4consumeFunction read elem:
11,110,1100 lfq-size:4
main constructed elem:16,160,1600 lfq-size:5
consumeFunction read elem:12,120,1200 lfq-size:4
main constructed elem:17,170,1700 lfq-size:5consumeFunction read elem:
13,130,1300 lfq-size:4
main constructed elem:18,180,1800 lfq-size:4consumeFunction read elem:
14,140,1400 lfq-size:4
main constructed elem:19,190,1900 lfq-size:5
consumeFunction read elem:15,150,1500 lfq-size:4
main constructed elem:20,200,2000 lfq-size:consumeFunction read elem:416,160,1600 lfq-size:4

main constructed elem:21,210,2100 lfq-size:5
consumeFunction read elem:17,170,1700 lfq-size:4
main constructed elem:22,220,2200 lfq-size:4consumeFunction read elem:
18,180,1800 lfq-size:4
main constructed elem:23,230,2300 lfq-size:4consumeFunction read elem:
19,190,1900 lfq-size:4
main constructed elem:24,240,2400 lfq-size:consumeFunction read elem:420,200,2000 lfq-size:4

main constructed elem:25,250,2500 lfq-size:consumeFunction read elem:4
21,210,2100 lfq-size:4
main constructed elem:26,260consumeFunction read elem:,222600, lfq-size:220,2200 lfq-size:44

main constructed elem:27,270consumeFunction read elem:,23,2302700, lfq-size:2300 lfq-size:4
4
main constructed elem:28,280,2800 lfq-size:5
consumeFunction read elem:24,240,2400 lfq-size:4
main constructed elem:29,290,2900 lfq-size:4consumeFunction read elem:
25,250,2500 lfq-size:4
main constructed elem:30,300,3000 lfq-size:5
consumeFunction read elem:26,260,2600 lfq-size:4
main constructed elem:31,310,3100 lfq-size:5
consumeFunction read elem:27,270,2700 lfq-size:4
main constructed elem:32,320,3200 lfq-size:4consumeFunction read elem:
28,280,2800 lfq-size:4
main constructed elem:33,330,3300 lfq-size:4consumeFunction read elem:
29,290,2900 lfq-size:4
main constructed elem:34,340,3400 lfq-size:consumeFunction read elem:430,300,3000 lfq-size:4

main constructed elem:35,350,3500 lfq-size:4consumeFunction read elem:
31,310,3100 lfq-size:4
main constructed elem:36,360,3600 lfq-size:5
consumeFunction read elem:32,320,3200 lfq-size:4
main constructed elem:37,370,3700 lfq-size:consumeFunction read elem:433,
330,3300 lfq-size:4
main constructed elem:consumeFunction read elem:3834,340,3400 lfq-size:4
,380,3800 lfq-size:4
main constructed elem:39,390,3900 lfq-size:consumeFunction read elem:435,350,3500 lfq-size:4

main constructed elem:40,400,4000 lfq-size:consumeFunction read elem:436,360,
3600 lfq-size:4
main constructed elem:41,410,4100 lfq-size:5
consumeFunction read elem:37,370,3700 lfq-size:4
main constructed elem:42,420,4200 lfq-size:consumeFunction read elem:438,380,3800 lfq-size:4

main constructed elem:43,430,4300 lfq-size:5
consumeFunction read elem:39,390,3900 lfq-size:4
main constructed elem:44,440,4400 lfq-size:consumeFunction read elem:440,400,4000 lfq-size:4

main constructed elem:45,450,4500 lfq-size:consumeFunction read elem:441,410,4100 lfq-size:4

main constructed elem:46,460,4600 lfq-size:consumeFunction read elem:442,420,4200 lfq-size:4

main constructed elem:47,470,4700 lfq-size:consumeFunction read elem:443,430,4300 lfq-size:4

main constructed elem:48,480,4800 lfq-size:consumeFunction read elem:444,440,4400 lfq-size:
4
consumeFunction read elem:45,450,4500 lfq-size:3
main constructed elem:49,490,4900 lfq-size:4
consumeFunction read elem:46,460,4600 lfq-size:3
consumeFunction read elem:47,470,4700 lfq-size:2
consumeFunction read elem:48,480,4800 lfq-size:1
consumeFunction read elem:49,490,4900 lfq-size:0
consumeFunction exiting.
main exiting.
*/