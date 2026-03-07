#include <list>
#include <vector>

namespace Containers
{
    enum QUADRANT{NW, NE, SW, SE};
    enum DIRECTION{LEFT, RIGHT, BOTH};
    enum AXIS{XA, YA};

    // Forward class declarations
    class CRectangle;
    class CBinNode;
    class CQuadNode;

    // Helper functions
    QUADRANT CIF_COMPARE(CRectangle* pP, const double CX, const double CY);
    DIRECTION BIN_COMPARE(CRectangle* pP, const double CV, const AXIS V);

    bool CIF_SEARCH(CRectangle* pP, CQuadNode* pQ, 
                         const double CX, const double CY,
                         double LX, double LY);

    bool CROSS_AXIS(CRectangle* pP, CBinNode* pQ, 
                         const double CV, double LV, const AXIS V);

    QUADRANT  OPQUAD(const QUADRANT Q);
    QUADRANT  CQUAD (const QUADRANT Q);
    QUADRANT  CCQUAD(const QUADRANT Q);

    DIRECTION OPDIR(const DIRECTION D);

    AXIS OTHERAXIS(const AXIS V);    

    class CRectangle
    {
    public:
        CRectangle(double cx = 0.0, double cy = 0.0, double lx = 0.0, double ly = 0.0);
        CRectangle(const CRectangle& P);

        ~CRectangle();

        double GetCenterX() const;
        double GetCenterY() const;
        double GetWidth() const;
        double GetHeight() const;

        CRectangle& operator= (const CRectangle& P);

        bool Intersects(const CRectangle& P);

    private:
        double m_cx, m_cy;
        double m_lx, m_ly;

    friend QUADRANT  CIF_COMPARE(CRectangle*, const double, const double);
    friend DIRECTION BIN_COMPARE(CRectangle*, const double, const AXIS);

    friend class CMxCifQuadTree;
    };

    class CBinNode
    {
    private:
        CBinNode();
        ~CBinNode();

        void Insert(CRectangle* pP);
        bool Holds (CRectangle* pP);
        void Remove(CRectangle* pP);

        int GetSize();

        std::list<CRectangle*> m_Rectangles;
        CBinNode*              m_Child[2];

    friend bool CROSS_AXIS(CRectangle*, CBinNode*,
                            const double, double, const AXIS);

    friend class CQuadNode;
    friend class CMxCifQuadTree;
    };

    class CQuadNode
    {
    private:
        CQuadNode();
        ~CQuadNode();

        void InsertOnAxis(CRectangle* pP, double CV, double LV, AXIS V);

        CBinNode*   m_Axis[2];
        CQuadNode*  m_Child[4];

    friend bool CIF_SEARCH(CRectangle*, CQuadNode*, 
                            const double, const double,
                            double, double);

    friend class CMxCifQuadTree;
    };

    class CMxCifQuadTree
    {
    public:
        CMxCifQuadTree(const CRectangle& P);
        ~CMxCifQuadTree();

        void Insert     (CRectangle* pP);
        void Remove     (CRectangle* pP);
        bool Intersects (CRectangle* pP);

        void Clear();

    private:
        CRectangle  m_P;
        CQuadNode*  m_Root;
    };
}