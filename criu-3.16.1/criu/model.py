import torch.nn as nn
import torch
# from dataset import batch_number
# from data_process import predict_length, train_window
class SSDP(nn.Module):
    def __init__(self, input_size, hidden_layer_size, output_size, head_num, batch_size):
        super().__init__()
        self.hidden_layer_size = hidden_layer_size
        self.batch_size = batch_size
        self.lstm1 = nn.LSTM(input_size, hidden_layer_size, 1, batch_first = True)
        self.lstm2 = nn.LSTM(input_size, hidden_layer_size, 1, batch_first = True)
        self.linear1 = nn.Linear(self.batch_size*7, self.batch_size*hidden_layer_size)
        self.attention = nn.MultiheadAttention(hidden_layer_size, head_num)
        self.linear2_1 = nn.Linear(batch_size * 3 * hidden_layer_size, batch_size * 1)
        self.linear2_2 = nn.Linear(batch_size * 3 * hidden_layer_size, batch_size * 1)
        self.linear2_3 = nn.Linear(batch_size * 3 * hidden_layer_size, batch_size * 1)
        self.sigmoid_fun = nn.Sigmoid()
    def forward(self, input_seq):
        lstm_out1, self.hidden_cell1 = self.lstm1(input_seq[0].view(self.batch_size ,self.hidden_layer_size, -1), self.hidden_cell1)
        lstm_out2, self.hidden_cell2 = self.lstm2(input_seq[1].view(self.batch_size ,self.hidden_layer_size, -1), self.hidden_cell2)
        lstm_out1 = lstm_out1.unsqueeze(2)
        lstm_out2 = lstm_out2.unsqueeze(2)
        final_output1 = lstm_out1.squeeze(2)[:, -1, :].view(self.batch_size, 1, self.hidden_layer_size)
        final_output2 = lstm_out2.squeeze(2)[:, -1, :].view(self.batch_size, 1, self.hidden_layer_size)
#         print(final_output1.shape)
#         print(final_output2.shape)
#         print(self.hidden_cell1[0].shape)
#         print(self.hidden_cell2[0].shape)
        input_seq[2] = input_seq[2].view(1, 1, self.batch_size*7)
        sys_out = self.linear1(input_seq[2]).view(self.batch_size, 1, -1)
#         print(sys_out.shape)
        res = torch.cat((final_output1,final_output2,sys_out), dim = 1)
#         print(res.shape)
        out,_ = self.attention(res, res, res)
#         print(out.shape)
        f_out = out.view(1, -1)
#         print(f_out.shape)
        pre1 = self.sigmoid_fun(self.linear2_1(f_out)).view(self.batch_size, -1)
        pre2 = self.sigmoid_fun(self.linear2_2(f_out)).view(self.batch_size, -1)
        pre3 = self.sigmoid_fun(self.linear2_3(f_out)).view(self.batch_size, -1)
        predictions = torch.cat((pre1, pre2, pre3), dim=1)
        return predictions
