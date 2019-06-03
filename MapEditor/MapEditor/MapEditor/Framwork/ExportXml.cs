using MapEditor.Algorithm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml;

namespace MapEditor.Framwork
{
    public class ExportXml
    {
        private static ExportXml mInstance;
        private XmlWriter mWriter;

        public XmlWriter MWriter
        {
            get { return mWriter; }
            set { mWriter = value; }
        }
        XmlWriterSettings mWriterXmlSettings;

        private ExportXml()
        {
            mWriterXmlSettings = new XmlWriterSettings();
            mWriterXmlSettings.Indent = true;
            mWriterXmlSettings.ConformanceLevel = ConformanceLevel.Document;
            mWriter = XmlWriter.Create("map.xml", mWriterXmlSettings);
        }

        public static ExportXml getInstance()
        {
            if(mInstance == null)
            {
                mInstance = new ExportXml();
            }

            return mInstance;
        }

        public bool writeXmlFile(List<OBJECT> _listObject)
        {
            if (mWriter != null && _listObject != null)
            {
                mWriter.WriteStartElement("Objects");
                for (int i = 0; i < _listObject.Count; ++i)
                {
                    writeElement(_listObject[i]);
                }
                mWriter.WriteEndElement();
                mWriter.Close();
                return true;
            }

            return false;
        }

        public void writeElement(OBJECT _object)
        {
            mWriter.WriteStartElement("Object");
            VECTOR2D temp = new VECTOR2D();
            temp = Support.ConvertCoordination(_object);
            mWriter.WriteAttributeString("Type", Convert.ToString(_object.Type));
            mWriter.WriteAttributeString("Id", Convert.ToString(_object.ID));
            mWriter.WriteAttributeString("X", Convert.ToString(temp.cX));
            mWriter.WriteAttributeString("Y", Convert.ToString(temp.cY));
            if (_object.Type == 1)
            {
                mWriter.WriteAttributeString("Width", Convert.ToString(_object.Bound.width));
                mWriter.WriteAttributeString("Height", Convert.ToString(_object.Bound.height));
            }
            mWriter.Flush();
            mWriter.WriteEndElement();
        }

        public void writeGridToXml(CNode Grid, XmlWriter writer)
        {
            if (Grid != null)
            {
                mWriter.WriteStartElement("Cell");
                mWriter.WriteAttributeString("Id", Convert.ToString(Grid.ID));
                mWriter.WriteAttributeString("X", Convert.ToString(Grid.Bound.cX));
                mWriter.WriteAttributeString("Y", Convert.ToString(Grid.Bound.cY));
                mWriter.WriteAttributeString("Width", Convert.ToString(Grid.Bound.width));
                mWriter.WriteAttributeString("Height", Convert.ToString(Grid.Bound.height));
                {
                    mWriter.WriteStartElement("Objects"); 
                    for (int i = 0; i < Grid.ListObject.Count; ++i)
                    {
                        mWriter.WriteStartElement("Object");
                        mWriter.WriteAttributeString("Type", Convert.ToString(Grid.ListObject[i].Type));
                        mWriter.WriteAttributeString("Id", Convert.ToString(Grid.ListObject[i].ID));
                        mWriter.WriteAttributeString("Index", Convert.ToString(Grid.ListObject[i].Index));
                        mWriter.WriteAttributeString("X", Convert.ToString(Grid.ListObject[i].Position.cX));
                        mWriter.WriteAttributeString("Y", Convert.ToString(Grid.ListObject[i].Position.cY));
                        mWriter.WriteAttributeString("Width", Convert.ToString(Grid.ListObject[i].Bound.width));
                        mWriter.WriteAttributeString("Height", Convert.ToString(Grid.ListObject[i].Bound.height));

                        mWriter.WriteEndElement();
                    }
                    mWriter.WriteEndElement();
                }

                mWriter.WriteEndElement();
            }
        }
        public bool DestroyWriter()
        {
            if (mWriter != null)
            {
                mWriter = null;

                return true;
            }
            return false;
        }

        public void WriteInfomationForMap()
        {
            mWriter.WriteStartElement("Map");
            mWriter.WriteAttributeString("Name", "1");
            mWriter.WriteAttributeString("Width", Support.WIDTH_MAP.ToString());
            mWriter.WriteAttributeString("Height", Support.HEIGHT_MAP.ToString());
            //mWriter.WriteEndElement();
        }
    }
}