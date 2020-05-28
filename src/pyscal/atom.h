#include <iostream>
#include <exception>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <complex>

namespace py = pybind11;
using namespace std;


const double PI = 3.141592653589793;
const int MAXNUMBEROFNEIGHBORS = 100;
const int NILVALUE = 333333;
const int MAXRADFUNCS = 10;
//create a structure for sorting
struct datom{
    double dist;
    int  index;
};

//create another for the sorting algorithm
struct by_dist{
    bool operator()(datom const &datom1, datom const &datom2){
        return (datom1.dist < datom2.dist);
    }
};


class Atom{
    /*
    Class to hold the details of an atom. This is a list of all
    members of the class.
    Attributes
    ----------
    Basic atom properties
    ---------------------
    posx : float
        x coordinate of atom
    posy : float
        y coordinate of atom
    posz : float
        z coordinate of atom
    id : int
        id of the atom
    loc : int
        location of the atom in the array of all atoms in
        the system.
    Neighbor related properties
    ---------------------------
    n_neighbors : int
        number of neighbors of the atom
    Cluster related properties
    --------------------------
    frenkelnumber : int
        frenkelnumber of the atom.
    issolid : int
        0 or 1. 1 if atom is solid.
    structure : int
        structure of the atom.
    belongsto : int
        id of the cluster to which atom belongs to.
     */
    public:
        Atom(vector<double>, int, int);
        virtual ~Atom();

        //basic atom properties
        double posx,posy,posz;
        int id;
        int loc;

        py::dict custom;
        py::dict gcustom();
        void scustom(py::dict);

        //neighbor related properties
        int neighbors[MAXNUMBEROFNEIGHBORS];
        double neighbordist[MAXNUMBEROFNEIGHBORS];
        double neighborweight[MAXNUMBEROFNEIGHBORS];
        int facevertices[MAXNUMBEROFNEIGHBORS];
        int faceverticenumbers[MAXNUMBEROFNEIGHBORS];
        double faceperimeters[MAXNUMBEROFNEIGHBORS];
        //double edgelengths[MAXNUMBEROFNEIGHBORS];
        double n_diffx[MAXNUMBEROFNEIGHBORS];
        double n_diffy[MAXNUMBEROFNEIGHBORS];
        double n_diffz[MAXNUMBEROFNEIGHBORS];
        double n_r[MAXNUMBEROFNEIGHBORS];
        double n_phi[MAXNUMBEROFNEIGHBORS];
        double n_theta[MAXNUMBEROFNEIGHBORS];
        double sij[MAXNUMBEROFNEIGHBORS];
        int n3, n4, n5, n6;
        int n_neighbors;
        vector<datom> temp_neighbors;




        //vertex vectors
        vector<vector<double>> edgelengths;
        vector<double> vertex_vectors;
        vector<int> vertex_numbers;
        vector<double> gvertex_vectors();
        void svertex_vectors(vector<double>);
        vector<int> gvertex_numbers();
        void svertex_numbers(vector<int>);



        double realQ6[13],imgQ6[13];

        int frenkelnumber;
        double avq6q6;
        //volume calculated by voronoi tesselation
        double volume;
        double avgvolume;
        double gvolume();
        double gavgvolume();
        void svolume(double);
        void savgvolume(double);
        double gasij();
        void sasij(double);

        int belongsto;
        void scluster(int);
        int gcluster();

        int lcluster;
        void slcluster(int);
        int glcluster();

        int issurface;
        void ssurface(int);
        int gsurface();

        int issolid;
        int structure;
        int type;
        int condition;

        //mask for calculations to exclude atoms
        bool mask;
        void smask(bool);
        bool gmask();

        double cutoff;
        void scutoff(double);
        double gcutoff();


        //indicator which is 1 if neighbors are already provided
        int isneighborset;

        //we need some functions to fetch atom properties
        vector<double> gx();
        void sx(vector<double>);
        //int* gx();
        //double gy();
        //double gz();
        //probably wont work
        //in that case will have to return a vector
        //its probably expensive
        //but that doesnt matter because we wont use it regularl

        //function to set neighbors
        void sneighdist(vector<double>);
        vector<double> gneighdist();
        void ssij(vector<double>);
        vector<double> gsij();
        void sneighbors(vector<int> nns);
        vector<int> gneighbors();
        vector<int> gfacevertices();
        void sfacevertices(vector<int>);
        vector<double> gfaceperimeters();
        void sfaceperimeters(vector<double>);
        vector<vector<double>> gedgelengths();
        void sedgelengths(vector<vector<double>>);
        vector<int> gvorovector();
        void svorovector(vector<int>);

        int gnneighbors();
        void snneighbors(int);
        void sneighborweights(vector<double> nns);
        vector<double> gneighborweights();
        //vector<double> gx();
        //variables for storing q2-12
        //invidual variables or arrays - individual ones are easier!
        double q[MAXRADFUNCS][11];
        double aq[MAXRADFUNCS][11];

        //access functions are to be added
        double realq[MAXRADFUNCS][11][25];
        double imgq[MAXRADFUNCS][11][25];
        double arealq[MAXRADFUNCS][11][25];
        double aimgq[MAXRADFUNCS][11][25];
        vector<complex<double>> get_qcomps(int, int, bool);


        vector<vector<double>> gallq();
        vector<vector<double>> gallaq();
        void sallq(vector<vector<double>>);
        void sallaq(vector<vector<double>>);

        double gq(int, int);
        void sq(int, double, int);

        double gq_big(int, int, bool);
        void sq_big( int, double, int, bool);
        vector<double> gq_big(vector<int>,int,  bool);
        void sq_big(vector<int>, vector<double>, int, bool);

        //vector <vector<double>> gqlm(int);

        double gaq(int);
        int gid();
        void sid(int);
        int gloc();
        void sloc(int);
        int gtype();
        void stype(int);
        void saq(int, double);
        //vector <vector<double>> gaqlm(int);

        int gsolid();
        void ssolid(int);
        int gstructure();
        void sstructure(int);


        void scondition(int);
        int gcondition();

        int gfrenkelnumber();
        void sfrenkelnumber(int);


        //costheta stuff
        double angular;
        double avg_angular;
        double gangular();
        void sangular(double);
        double gavgangular();
        void savgangular(double);
        //vector<vector<vector<double>>> gallqcomps();
        //void sallqcomps(vector<vector<vector<double>>>);
        vector<int> chiparams;
        vector<int> gchiparams();
        void schiparams(vector<int>);

        //for cell list implementation
        int head;

        //intermediate values for disorder params
        //the value of self dot product
        double sii;

        //disorder params
        double disorder;
        double avgdisorder;
        double gdisorder();
        void sdisorder(double);
        double gavgdisorder();
        void savgdisorder(double);

        //method for sro
        vector<double> sro;
        vector<double> gsro();
        void ssro(vector<double>);

        //additions for version 3
        int rad; //indicates if radial params are calculated or not
};
