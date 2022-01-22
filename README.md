using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Google.Cloud.Firestore; 

namespace MPS_ADMIN
{
    public partial class workForm : Form
    {
        private string _machine_id;
        private string _name;
        private string _pass;

        private AnalysisScreen analysisScreen = new AnalysisScreen();
        private HomeScreen hscr = new HomeScreen();
        public workForm()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void btHome_Click(object sender, EventArgs e)
        {
            panelScreen.Controls.Clear();

            hscr.TopLevel = false;
            panelScreen.Controls.Add(hscr); 
            hscr.Show();
        }

        private void btBase_Click(object sender, EventArgs e)
        {
            panelScreen.Controls.Clear();
            analysisScreen.TopLevel = false;
            panelScreen.Controls.Add(analysisScreen);
            analysisScreen.Show();
        }

        private void workForm_Load(object sender, EventArgs e)
        {
            panelScreen.Controls.Clear();
            hscr.TopLevel = false;
            panelScreen.Controls.Add(hscr);
            hscr.Show();
        }

        private void workForm_Resize(object sender, EventArgs e)
        {
            //MessageBox.Show("HIHI"); 
            flowLayoutPanel1.Height = this.Height;
            panelScreen.Size = new System.Drawing.Size(this.Width - flowLayoutPanel1.Width, this.Height);

            hscr.ClientSize = new System.Drawing.Size(this.Width - flowLayoutPanel1.Width, this.Height);
            analysisScreen.ClientSize = new System.Drawing.Size(this.Width - flowLayoutPanel1.Width, this.Height);
        }

        private void workForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            
            DialogResult result = MessageBox.Show("Bạn Có muốn đóng ứng dụng", "Thông báo", MessageBoxButtons.YesNo, MessageBoxIcon.Question); 
            if (result == DialogResult.Yes)
            {
                System.Windows.Forms.Application.ExitThread(); 
            }
            if(result == DialogResult.No)
            {
                e.Cancel = true; 
                base.OnClosed(e); 
            }
            
        }
    }
}
