using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WFCompilerUI
{
    public partial class Form1 : Form
    {
        private string currentFilename;
        Compilador.Manager compiler;
        public Form1()
        {
            InitializeComponent();
            currentFilename = "";
            compiler = new Compilador.Manager();
        }

        private void quickSave()
        {
            string str_code = Input.Text.Trim();
            StreamWriter writer = new StreamWriter(currentFilename, false);
            writer.Write(str_code);
            writer.Flush();
            writer.Close();
        }

        private void saveCode()
        {
            SaveFileDialog saveDialog = new SaveFileDialog();
            saveDialog.Filter = "Text file(.txt)|*.txt | All Files(*.*)|*.*";
            saveDialog.Title = "Save code";
            saveDialog.ShowDialog();
            if(saveDialog.FileName != "")
            {
                currentFilename = saveDialog.FileName;
                quickSave();
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
            if(currentFilename == "")
            {
                saveCode();
            }
            else
            {
                quickSave();
            }
        }

        private void compilarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] details = compiler.compile(Input.Text);
            Output.Lines = details;
            string[] tokens = compiler.getAllTokens();
            DebugOutput.Lines = tokens;
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveCode();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Input.Text.Trim() == "")
            {
                Application.Exit();
            }
        }

        private void OpenDoc()
        {
            OpenFileDialog openFile = new OpenFileDialog();
            openFile.Filter = "Text file(.txt)|*.txt| All Files(*.*)|*.*";
            openFile.FilterIndex = 1;
            openFile.Title = "Open File";
            if (openFile.ShowDialog() == DialogResult.OK)
            {
                StreamReader lector = new StreamReader(File.OpenRead(openFile.FileName));
                Input.Text = lector.ReadToEnd();
                lector.Dispose();
            }
            currentFilename = openFile.FileName;
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Input.Text.Trim() != "")
            {
                DialogResult result = MessageBox.Show("Desea guardar el documento?", "Guardar?", MessageBoxButtons.YesNoCancel);
                if (result == DialogResult.Yes)
                {
                    quickSave();
                    OpenDoc();
                }
                else if (result == DialogResult.No)
                {
                    OpenDoc();
                }
            }
            else
            {
                OpenDoc();
            }
        }
    }
}
