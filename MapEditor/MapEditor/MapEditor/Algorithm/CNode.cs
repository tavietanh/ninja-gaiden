using MapEditor.Framwork;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace MapEditor.Algorithm
{
    public enum PositionOfNode
    {
        TopLeft = 1,
        TopRight = 2,
        BottomLeft = 3,
        BottomRight = 4,
    }

    public class CNode
    {
        public static int MAX_SIZE_OF_COLLISION = 2;
        private CNode m_next;

        public CNode Next
        {
            get { return m_next; }
            set { m_next = value; }
        }

        private int m_id;
        private RECTANGLE m_bound;
        private List<OBJECT> m_listObject;

        private static int MAX_WIDTH_SIZE_OF_NODE = 256;
        private static int MAX_HEIGHT_SIZE_OF_NODE = 256;

        #region.Properties
        public int ID
        {
            get { return this.m_id; }
            set { this.m_id = value; }
        }

        public RECTANGLE Bound
        {
            get { return this.m_bound; }
            set { this.m_bound = value; }
        }

        public List<OBJECT> ListObject
        {
            get { return this.m_listObject; }
            set { this.m_listObject = value; }
        }
        #endregion

        public int getParent()
        {
            return this.m_id / 10;
        }

        public List<OBJECT> getListObject()
        {
            return this.m_listObject;
        }

        public CNode(int ID, RECTANGLE Bound)
        {
            // if node is root
            this.m_id = ID;

            this.m_next = null;

            this.m_listObject = new List<OBJECT>();
            if (ID == 0)
            {
                this.m_bound = Bound;
            }
            else
            {
                this.m_bound = new RECTANGLE(Bound.cX + Support.SIZE_CELLS, Bound.cY, Support.SIZE_CELLS, Support.SIZE_CELLS);
            }
        }

        public void InsertObject(CNode node, OBJECT obj)
        {
            
            RECTANGLE rect = RECTANGLE.Intersec(node.m_bound, obj.RangeOfMovement);
                    
            if (rect.cX == 0 && rect.cY == 0 && rect.width == 0 && rect.height == 0)
            {
                return ;
            }
            node.m_listObject.Add(obj);

            return;
        }

        //public bool IsParent()
        //{
        //    if (this.m_tl != null)
        //        return true;

        //    return false;
        //}
    }
}
