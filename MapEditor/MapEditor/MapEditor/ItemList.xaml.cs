using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace MapEditor
{
    /// <summary>
    /// Interaction logic for ItemList.xaml
    /// </summary>
    public partial class ItemList : Window
    {
        private Canvas workspace;
        private System.Windows.Point positionOfItem;

        public ItemList(Canvas _workspace, System.Windows.Point _position)
        {
            InitializeComponent();
            workspace = _workspace;
            positionOfItem = _position;
        }

        private void RadioButton_Checked_1(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (rb5power.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rb10power.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rb500point.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rb1000point.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbFlames.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbThrowStar.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbTimeFreezy.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbWindmilStar.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            else if (rbHealth.IsChecked == true)
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

                        Canvas.SetLeft(image, (double)positionOfItem.X);
                        Canvas.SetTop(image, (double)positionOfItem.Y);
                        workspace.Children.Add(image);
                    }
                }
            }
            this.Close();
        }
    }
}
