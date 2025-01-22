using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Accw;

namespace WPCommSharpClient
{
	public partial class MainView : Form
	{

		private WPCallbackClient client;
		private MTSCBServerClass server;

		// This delegate enables asynchronous calls for setting
		// the text property on a TextBox control.
		private delegate void InsertMessageCallback(string text);

		private Thread messageProcessor;

		public MainView()
		{
			InitializeComponent();

			try
			{
				client = new WPCallbackClient();
				server = new MTSCBServerClass();
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, "Error on creating MTSCBServer instance");
				throw;
			}
		}

		private void btnLogin_Click(object sender, EventArgs e)
		{
			int iUserID = 1;
			bool bConnected = false;
			
			try 
			{	        
			  if (string.IsNullOrWhiteSpace(txtDomain.Text.Trim()))
                    bConnected = server.InitServer(client, 3, txtUserName.Text, txtPassword.Text, iUserID);
              else
                    bConnected = server.InitServer2(client, 3, txtUserName.Text, txtPassword.Text, txtDomain.Text, iUserID);
			}
			catch (Exception ex)
			{
				throw;
			}

			if(bConnected)
			{
				MessageBox.Show("Login success");
				messageProcessor = new Thread(ProcessMessages);
				messageProcessor.IsBackground = true;
				messageProcessor.Start();
			}
		}

		private void ProcessMessages()
		{
			while(true)
			{
				lock (client.messageQueue)
				{
					if (client.messageQueue.Count > 0)
					{
						string sMessage = client.messageQueue.Dequeue();
						InsertMessage(sMessage);
					}
				}    
			}
		}

		private void InsertMessage(string message)
		{
			if (this.InvokeRequired)
			{
				this.Invoke(new InsertMessageCallback(InsertMessage), new object[] { message });
				return;
			}

			listMessages.Items.Add(message);
		}

		private void logoutToolStripMenuItem_Click(object sender, EventArgs e)
		{
			int iConnected = 0;
			server.IsConnected(out iConnected);
			if(iConnected > 0)
				server.DoneServer(client);
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			int iConnected = 0;
			server.IsConnected(out iConnected);
			if (iConnected > 0)
				server.DoneServer(client);

			this.Close();

		}
	}
}
