#ifndef MODULE_H
#define MODULE_H

class Module {
    public:
        virtual ~Module() {};
        virtual void execute() =0;
        virtual int render() =0;
};

#endif
