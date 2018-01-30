namespace WFCompilerUI
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.Input = new System.Windows.Forms.TextBox();
            this.Output = new System.Windows.Forms.TextBox();
            this.Menu = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.New = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SaveMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.compileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.compilarToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DebugOutput = new System.Windows.Forms.TextBox();
            this.Menu.SuspendLayout();
            this.SuspendLayout();
            // 
            // Input
            // 
            this.Input.Location = new System.Drawing.Point(12, 31);
            this.Input.Multiline = true;
            this.Input.Name = "Input";
            this.Input.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.Input.Size = new System.Drawing.Size(881, 370);
            this.Input.TabIndex = 0;
            // 
            // Output
            // 
            this.Output.Font = new System.Drawing.Font("Courier New", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Output.Location = new System.Drawing.Point(12, 416);
            this.Output.Multiline = true;
            this.Output.Name = "Output";
            this.Output.ReadOnly = true;
            this.Output.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.Output.Size = new System.Drawing.Size(881, 85);
            this.Output.TabIndex = 1;
            // 
            // Menu
            // 
            this.Menu.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.Menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.compileToolStripMenuItem});
            this.Menu.Location = new System.Drawing.Point(0, 0);
            this.Menu.Name = "Menu";
            this.Menu.Size = new System.Drawing.Size(905, 28);
            this.Menu.TabIndex = 2;
            this.Menu.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.New,
            this.openToolStripMenuItem,
            this.SaveMenuItem,
            this.saveAsToolStripMenuItem,
            this.toolStripMenuItem2,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // New
            // 
            this.New.Name = "New";
            this.New.Size = new System.Drawing.Size(142, 26);
            this.New.Text = "New";
            this.New.Click += new System.EventHandler(this.NewMenuItem);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(142, 26);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // SaveMenuItem
            // 
            this.SaveMenuItem.Name = "SaveMenuItem";
            this.SaveMenuItem.Size = new System.Drawing.Size(142, 26);
            this.SaveMenuItem.Text = "Save";
            this.SaveMenuItem.Click += new System.EventHandler(this.SaveMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(142, 26);
            this.saveAsToolStripMenuItem.Text = "Save as...";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(139, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(142, 26);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // compileToolStripMenuItem
            // 
            this.compileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.compilarToolStripMenuItem});
            this.compileToolStripMenuItem.Name = "compileToolStripMenuItem";
            this.compileToolStripMenuItem.Size = new System.Drawing.Size(77, 24);
            this.compileToolStripMenuItem.Text = "Compile";
            // 
            // compilarToolStripMenuItem
            // 
            this.compilarToolStripMenuItem.Name = "compilarToolStripMenuItem";
            this.compilarToolStripMenuItem.Size = new System.Drawing.Size(181, 26);
            this.compilarToolStripMenuItem.Text = "Compilar";
            this.compilarToolStripMenuItem.Click += new System.EventHandler(this.compilarToolStripMenuItem_Click);
            // 
            // DebugOutput
            // 
            this.DebugOutput.Location = new System.Drawing.Point(12, 507);
            this.DebugOutput.Multiline = true;
            this.DebugOutput.Name = "DebugOutput";
            this.DebugOutput.ReadOnly = true;
            this.DebugOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.DebugOutput.Size = new System.Drawing.Size(881, 94);
            this.DebugOutput.TabIndex = 3;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(905, 613);
            this.Controls.Add(this.DebugOutput);
            this.Controls.Add(this.Output);
            this.Controls.Add(this.Input);
            this.Controls.Add(this.Menu);
            this.MainMenuStrip = this.Menu;
            this.Name = "Form1";
            this.Text = "Compiler";
            this.Menu.ResumeLayout(false);
            this.Menu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Input;
        private System.Windows.Forms.TextBox Output;
        private System.Windows.Forms.MenuStrip Menu;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem New;
        private System.Windows.Forms.ToolStripMenuItem compileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SaveMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem compilarToolStripMenuItem;
        private System.Windows.Forms.TextBox DebugOutput;
    }
}

