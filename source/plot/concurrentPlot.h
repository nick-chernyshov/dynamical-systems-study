#ifndef CONCURRENTPLOT_H
#define CONCURRENTPLOT_H

#include <thread>
#include <mutex>
#include <list>

using namespace std;

template<size_t state_size, size_t param_size>
struct ConcurrentPlot : public ContourPlot<state_size, param_size> {

    mutex mtx_;
    list<params<param_size> > tasks_;
    static const size_t threadCount_ = 6;
    Equations<state_size, param_size> * ds_;
    fstream file_;


    ConcurrentPlot(state<state_size> initS, params<param_size> pmin, params<param_size> pmax,
                Equations<state_size, param_size> * ds,
                Axes axes, Spans spans, double transitionTime) :
        ContourPlot<state_size, param_size>(initS,pmin, pmax,
                                            axes, spans, transitionTime)
    {
        s_ = initS;
        spans_ = spans;
        axes_ = axes;
        transitionTime_ = transitionTime;

        ds_ = ds;
    }

    virtual void computePoint(){};

    virtual void readPoint(fstream & f){}

    virtual void buildContourPlot()
    {
        file_.open(filename_, ios::in);
        if (file_.is_open())
        {
            readPoint(file_);
            file_.close();
            file_.open(filename_, ios::app);
        }
        else
        {
            file_.open(filename_, ios::out);
        }

        size_t & px = axes_.x;
        size_t & py = axes_.y;
        size_t & width = spans_.width;
        size_t & height = spans_.height;
        double dx = (pmax_[px] - pmin_[px])/width, dy = (pmax_[py] - pmin_[py])/height;
        params<param_size> p = pmin_;
        state<state_size> st = s_;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                p[px] = pmin_[px] + dx*i;
                p[py] = pmin_[py] + dy*j;

                if (built_points_.count(make_pair(p[px], p[py])))
                    continue;
                else
                {
                    tasks_.push_back(p);
                    built_points_.insert(make_pair(p[px], p[py]));
                }
            }
            file_.flush();
            std::cout << "row " << i << endl;
        }


        list<thread> threadPool;
        while (!tasks_.empty())
        {
            for (int i  = 0; i < threadCount_; i++)
            {
                threadPool.push_back(thread(&ConcurrentPlot::computePoint));
            }
            for (thread & threadItr : threadPool)
            {
                if (threadItr.joinable())
                    threadItr.join();
            }

            threadPool.clear();
        }


        file_.close();
    }

    virtual void readConfig(string ifName, Equations<state_size, param_size> & DS)= 0;

    virtual void readTask(string ifName) {

        fstream inpConf(ifName.c_str(), ifstream::in);

        string tmpStr("");

        stringstream s2vStream(stringstream::in | stringstream::out);
        int px = -1, py = -1;
        for (int i = 0; i < (int)param_size || py == -1; i++) {
            inpConf >> tmpStr;
            if (tmpStr != string(":")) {
                inpConf >> pmin_[i];
                s2vStream << tmpStr << string("=");
                s2vStream << pmin_[i] << string(" ");
            }
            else {
                i-- ;
                if (px == -1) {
                    px = i;
                }
                else {
                    py = i;
                }
                inpConf >> pmax_[i];
                s2vStream << string(" - ") << pmax_[i] << string(" ");
            }
        }

        for (int i = 0; i < (int)state_size; i++) {
            inpConf >> tmpStr >> s_[i];
            s2vStream << tmpStr << string("=") << s_[i] << " ";
        }

        size_t width = 0, height = 0;

        inpConf >> tmpStr >> width >> tmpStr >> height;
        s2vStream << string("w= ") << width << string(" h= ") << height << string(" ");

        filename_ = s2vStream.str()+".txt";

        inpConf.close();

        spans_.width = width;
        spans_.height = height;
        axes_.x = px;
        axes_.y = py;
    }

    virtual ~ConcurrentPlot(){}

};


#endif // CONCURRENTPLOT_H
