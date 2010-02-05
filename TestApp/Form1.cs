using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using AxPUTTYAXLib;

namespace TestApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                var objPuTTY = new AxPuttyAxObj();
                Controls.Add(objPuTTY);
                objPuTTY.Location = new Point(0, 0);
                objPuTTY.Size = new Size(400, 300);
                objPuTTY.Show();
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.ToString());
            }
        }
    }
}
