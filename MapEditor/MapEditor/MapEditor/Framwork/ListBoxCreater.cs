using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace MapEditor.Framwork
{
    public class ListBoxCreater
    {
        private static ListBoxCreater mListBoxCreater;

        private ListBoxCreater()
        {

        }

        public static ListBoxCreater getInstance()
        {
            if (mListBoxCreater == null)
            {
                mListBoxCreater = new ListBoxCreater();
            }

            return mListBoxCreater;
        }

        public static Image getImageForListBox(BitmapImage bmpImage, ObjectID id, int width, int height)
        {
            Image image = new Image();
            image.Tag = (int)id;
            image.Source = bmpImage;
            image.Width = width;
            image.Height = height;

            return image;
        }

        public void InitializeListBox(ListBox lbEnemyObject, ListBox lbLandObject, ListBox lbBoss1Object, ListBox lbBoss2Object = null, ListBox lbBoss3Object = null)
        {
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Ninja.png", UriKind.Relative)), ObjectID.NINJA, 17, 32));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_brown_bat.png", UriKind.Relative)), ObjectID.ENEMY_BROWN_BAT, 16, 13));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_eagle.png", UriKind.Relative)), ObjectID.ENEMY_EAGLE, 17, 25));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_machine_gun.png", UriKind.Relative)), ObjectID.ENEMY_MACHINE_GUN, 16, 32));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_panther.png", UriKind.Relative)), ObjectID.ENEMY_PANTHER, 24, 15));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_rocket.png", UriKind.Relative)), ObjectID.ENEMY_ROCKET, 24, 25));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_Sword.png", UriKind.Relative)), ObjectID.ENEMY_SWORD, 24, 32));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_throw_sword.png", UriKind.Relative)), ObjectID.ENEMY_THROW_SWORD, 24, 32));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\gif_bird.png", UriKind.Relative)), ObjectID.GIF_BIRD, 16, 15));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\gif_buterfly.png", UriKind.Relative)), ObjectID.GIF_BUTERFLY, 15, 14));
            lbEnemyObject.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Enemy_run.png", UriKind.Relative)), ObjectID.ENEMY_RUN, 16, 32));

            lbBoss1Object.Items.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\object\Boss3.png", UriKind.Relative)), ObjectID.BOSS_3, 34, 48));

            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\5power.png", UriKind.Relative)), ObjectID.OBJECT_5_POWER, 15, 15));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\10power.png", UriKind.Relative)), ObjectID.OBJECT_10_POWER, 15, 15));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\500point.png", UriKind.Relative)), ObjectID.OBJECT_500_POINT, 16, 15));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\1000point.png", UriKind.Relative)), ObjectID.OBJECT_1000_POINT, 16, 15));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\Flames.png", UriKind.Relative)), ObjectID.OBJECT_FLAMES, 16, 16));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\ThrowStar.png", UriKind.Relative)), ObjectID.OBJECT_THROW_STAR, 16, 16));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\TimeFreeze.png", UriKind.Relative)), ObjectID.OBJECT_TIME_FREEZE, 12, 15));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\WindmilStar.png", UriKind.Relative)), ObjectID.OBJECT_WINDMIL_STAR, 16, 16));
            Support.ListItem.Add(getImageForListBox(new BitmapImage(new Uri(@"\Resource\item\Health.png", UriKind.Relative)), ObjectID.OBJECT_HEALTH, 12, 16));
        }
    }
}
