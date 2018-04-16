using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void statusStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter_1(object sender, EventArgs e)
        {

        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(cb1.Checked && checkBox2.Checked && checkBox3.Checked && checkBox4.Checked && checkBox5.Checked && checkBox6.Checked && checkBox7.Checked && checkBox8.Checked && checkBox9.Checked)
            {
                lblDaily.Text = ("Great!");
            }
            else
            {
                MessageBox.Show("You haven't selecting the all daily tasks");
            }
            if(checkBox11.Checked && checkBox12.Checked && checkBox13.Checked && checkBox14.Checked && checkBox15.Checked && checkBox16.Checked && checkBox17.Checked && checkBox18.Checked && checkBox19.Checked && checkBox20.Checked)
            {
                lblWeekly.Text = ("Nice!");
            }
            else
            {
                MessageBox.Show("Make sure that you complete the Weekly list");
            }
            if(checkBox21.Checked && checkBox22.Checked && checkBox23.Checked && checkBox24.Checked && checkBox25.Checked && checkBox26.Checked && checkBox27.Checked && checkBox28.Checked && checkBox29.Checked && checkBox30.Checked)
            {
                lblMonthly.Text = ("FAFer");
            }
            else
            {
                MessageBox.Show("To become a FAFer check the lists");
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        int number_ch = 0;
        private void button3_Click(object sender, EventArgs e)
        {
           
            for (int i = 0; i <= number_ch; i++)
            {
                foreach (Control c in groupBox1.Controls)
                {
                    if (c.GetType().Name == "CheckBox")
                    {
                        if (((CheckBox)c).Checked == true)
                        {
                            groupBox1.Controls.Remove(c);
                            
                            number_ch--;
                        }
                    }
                }
                foreach (Control c in groupBox2.Controls)
                {
                    if (c.GetType().Name == "CheckBox")
                    {
                        if (((CheckBox)c).Checked == true)
                        {
                            groupBox2.Controls.Remove(c);

                            number_ch--;
                        }
                    }
                }
                foreach (Control c in groupBox3.Controls)
                {
                    if (c.GetType().Name == "CheckBox")
                    {
                        if (((CheckBox)c).Checked == true)
                        {
                            groupBox3.Controls.Remove(c);

                            number_ch--;
                        }
                    }
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            MessageBox.Show(this.Display.Items.Count.ToString(), "Total items");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Display.Items.Add(textBox1.Text);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            this.Display.Items.RemoveAt(Display.SelectedIndex); //for remove from listbox
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Display.Items.Insert(3, textBox1.Text);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            const string sPath = "SavedItems.txt";

            System.IO.StreamWriter SaveFile = new System.IO.StreamWriter(sPath);
            foreach (var item in Display.Items)
            {
                SaveFile.WriteLine(item);
            }

            SaveFile.Close();

            MessageBox.Show("Programs saved!");
        }
    }
}
