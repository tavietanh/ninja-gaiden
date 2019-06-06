using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Xml;

namespace MapEditor.Framwork
{
    public class ImportXml
    {
        private static ImportXml mInstance;
        private List<int> mReadList;

        public ImportXml()
        {
            this.mReadList = new List<int>();
        }

        public static ImportXml getInstance()
        {
            if (ImportXml.mInstance == null)
            {
                ImportXml.mInstance = new ImportXml();
            }

            return ImportXml.mInstance;
        }

        public bool isExisted(int index)
        {
            for (int i = 0; i < this.mReadList.Count; ++i)
            {
                if (index == this.mReadList[i])
                    return true;
            }

            return false;
        }

        public void loadCanvas(String pathFileName, Canvas workSpace)
        {
            XmlDocument xmlDocument = new XmlDocument();
            xmlDocument.Load(pathFileName);

            XmlNode rootNode;
            rootNode = xmlDocument.DocumentElement;

            Support.WIDTH_MAP = int.Parse(rootNode.Attributes["Width"].Value);
            Support.HEIGHT_MAP = int.Parse(rootNode.Attributes["Height"].Value);
            Support.MAPNAME = rootNode.Attributes["Name"].Value;
            
            XmlNodeList nodeList;
            nodeList = xmlDocument.GetElementsByTagName("Object");

            foreach (XmlNode item in nodeList)
            {
                if (this.isExisted(Convert.ToInt32(item.Attributes["Index"].Value)) == false)
                {
                    VECTOR2D tempPosition = new VECTOR2D(float.Parse(item.Attributes["X"].Value), float.Parse(item.Attributes["Y"].Value));
                    int width = Convert.ToInt32(item.Attributes["Width"].Value);
                    int height = Convert.ToInt32(item.Attributes["Height"].Value);

                    tempPosition = Support.ConvertCoordinationOfCanvas(tempPosition, width, height);

                    if (Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.VIRTUAL_OBJECT)
                    {
                        if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.TILE_BASE)
                        {
                            Rectangle shape = new Rectangle();
                            shape.Tag = (int)ObjectID.TILE_BASE;
                            shape.Width = width;
                            shape.Height = height;
                            shape.Stroke = new SolidColorBrush(Colors.Red);
                            shape.StrokeThickness = 3;

                            Canvas.SetLeft(shape, tempPosition.cX);
                            Canvas.SetTop(shape, tempPosition.cY);
                            Canvas.SetZIndex(shape, 2);
                            workSpace.Children.Add(shape);
                            this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                        }
                        else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.VIRTUAL_OBJECT_WALL)
                        {
                            Rectangle shape = new Rectangle();
                            shape.Tag = (int)ObjectID.VIRTUAL_OBJECT_WALL;
                            shape.Width = width;
                            shape.Height = height;
                            shape.Stroke = new SolidColorBrush(Colors.Blue);
                            shape.StrokeThickness = 3;

                            Canvas.SetLeft(shape, tempPosition.cX);
                            Canvas.SetTop(shape, tempPosition.cY);
                            Canvas.SetZIndex(shape, 2);
                            workSpace.Children.Add(shape);
                            this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                        }
                        else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.VIRTUAL_OBJECT_CLIMB)
                        {
                            Rectangle shape = new Rectangle();
                            shape.Tag = (int)ObjectID.VIRTUAL_OBJECT_CLIMB;
                            shape.Width = width;
                            shape.Height = height;
                            shape.Stroke = new SolidColorBrush(Colors.Green);
                            shape.StrokeThickness = 3;

                            Canvas.SetLeft(shape, tempPosition.cX);
                            Canvas.SetTop(shape, tempPosition.cY);
                            Canvas.SetZIndex(shape, 2);
                            workSpace.Children.Add(shape);
                            this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                        }
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.NINJA
                        && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Ninja.png", UriKind.Relative)), ObjectID.NINJA, 17, 32);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_BROWN_BAT
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_brown_bat.png", UriKind.Relative)), ObjectID.ENEMY_BROWN_BAT, 16, 13);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_RUN
                             && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_run.png", UriKind.Relative)), ObjectID.ENEMY_RUN, 16, 32);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_EAGLE
                            && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_eagle.png", UriKind.Relative)), ObjectID.ENEMY_EAGLE, 17, 25);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 3);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_MACHINE_GUN
                            && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_machine_gun.png", UriKind.Relative)), ObjectID.ENEMY_MACHINE_GUN, 16, 32);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_PANTHER
                          && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_panther.png", UriKind.Relative)), ObjectID.ENEMY_PANTHER, 24, 15);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_ROCKET
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_rocket.png", UriKind.Relative)), ObjectID.ENEMY_ROCKET, 24, 25);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_SWORD
                        && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_Sword.png", UriKind.Relative)), ObjectID.ENEMY_SWORD, 24, 32);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.ENEMY_THROW_SWORD
                       && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_throw_sword.png", UriKind.Relative)), ObjectID.ENEMY_THROW_SWORD, 24, 32);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.GIF_BIRD
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\gif_bird.png", UriKind.Relative)), ObjectID.GIF_BIRD, 16, 15);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.GIF_BUTERFLY
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\gif_buterfly.png", UriKind.Relative)), ObjectID.GIF_BUTERFLY, 15, 14);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.BOSS_3
                      && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        Image image = ListBoxCreater.getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Boss3.png", UriKind.Relative)), ObjectID.BOSS_3, 34, 48);
                        Canvas.SetLeft(image, tempPosition.cX);
                        Canvas.SetTop(image, tempPosition.cY);
                        Canvas.SetZIndex(image, 2);
                        workSpace.Children.Add(image);
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_5_POWER
                            && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_5_POWER)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_10_POWER
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_10_POWER)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_500_POINT
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_500_POINT)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if(Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_1000_POINT
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_1000_POINT)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if(Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_FLAMES
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_FLAMES)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_HEALTH
                          && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_HEALTH)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_THROW_STAR
                           && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_THROW_STAR)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_TIME_FREEZE
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_TIME_FREEZE)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                    else if (Convert.ToInt32(item.Attributes["Id"].Value) == (int)ObjectID.OBJECT_WINDMIL_STAR
                         && Convert.ToInt32(item.Attributes["Type"].Value) == (int)ObjectType.NORMAL_OBJECT)
                    {
                        for (int i = 0; i < Support.ListItem.Count; ++i)
                        {
                            if ((int)Support.ListItem[i].Tag == (int)ObjectID.OBJECT_WINDMIL_STAR)
                            {
                                Image image = new Image();
                                image.Source = Support.ListItem[i].Source;
                                image.Tag = Support.ListItem[i].Tag;
                                image.Width = Support.ListItem[i].Width;
                                image.Height = Support.ListItem[i].Height;

                                Canvas.SetLeft(image, (double)tempPosition.cX);
                                Canvas.SetTop(image, (double)tempPosition.cY);
                                Canvas.SetZIndex(image, 2);
                                workSpace.Children.Add(image);
                            }
                        }
                        this.mReadList.Add(Convert.ToInt32(item.Attributes["Index"].Value));
                    }
                }
            }
        }
    }
}
