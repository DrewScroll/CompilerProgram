using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WFCompilerUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void saveCode()
        {
            SaveFileDialog saveDialog = new SaveFileDialog();
            saveDialog.Filter = "Text file(.txt)|*.txt";
            saveDialog.Title = "Save code";
            saveDialog.ShowDialog();
            if(saveDialog.FileName != "")
            {

            }
        }

        private void NewMenuItem(object sender, EventArgs e)
        {
            if (Input.Text.Trim() != "")
            {
                DialogResult answer = MessageBox.Show("Guardar?", "Guardar?", MessageBoxButtons.YesNoCancel);
                if (answer == DialogResult.Yes)
                {
                    saveCode();
                }

                if (answer != DialogResult.Cancel)
                {
                    Input.Clear();
                }
            }
        }

        private void SaveMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
