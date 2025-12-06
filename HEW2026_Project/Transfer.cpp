#include "Transfer.h"


std::vector<std::string> Transfer::SplitCsvLine(const std::string& line, char delim)
{
	std::vector<std::string> cells;
	std::stringstream ss(line);
	std::string cell;
	while (std::getline(ss, cell, delim)) {
		cells.push_back(cell);
	}
	return cells;
}

std::string Transfer::JoinCsvLine(const std::vector<std::string>& cells, char delim)
{
	std::ostringstream oss;
	for (size_t i = 0; i < cells.size(); ++i) {
		oss << cells[i];
		if (i + 1 < cells.size()) {
			oss << delim;
		}
	}
	return oss.str();
}

bool Transfer::LoadTransferFromCsv(const std::string& path)
{
	TRAN_INS; // Transfer& tran = Transfer::GetInstance();

	std::ifstream in(path);
	if (!in.is_open()) {
		return false;
	}

	std::string line;
	size_t row = 0;

	while (std::getline(in, line)) {
		++row;

		// 1行目はヘッダ
		if (row == 1) {
			continue;
		}

		auto cells = SplitCsvLine(line, ',');
		if (cells.size() < 4) {
			continue; // 数値列が無ければスキップ
		}

		float v;
		try {
			v = std::stof(cells[3]); // 4列目「数値」
		}
		catch (...) {
			// 数値にならなければスキップ
			continue;
		}

		switch (row)
		{
		case 2:  tran.player.pos.x = v;                       break;
		case 3:  tran.player.pos.y = v;                       break;
		case 4:  /* ここは今は未使用。posをf3にしたらZに使う */  break;
		case 5:  tran.player.maxSpeed.x = v;
			tran.player.maxSpeed.y = v;                       break;
		case 6:  tran.player.velocity = v;                       break;

		case 7:  tran.stage.column = static_cast<int>(v);     break;
		case 8:  tran.stage.row = static_cast<int>(v);     break;

		case 9:  tran.camera.eyePos.x = v;                       break;
		case 10: tran.camera.eyePos.y = v;                       break;
		case 11: tran.camera.eyePos.z = v;                       break;

		case 12: tran.camera.lookPos.x = v;                       break;
		case 13: tran.camera.lookPos.y = v;                       break;
		case 14: tran.camera.lookPos.z = v;                       break;

		case 15: tran.item.downSpeed = v;                       break;
		case 16: tran.item.size.x = v;                       break;
		case 17: tran.item.size.y = v;                       break;
		case 18: tran.item.size.z = v;                       break;

		case 19: tran.order.size.x = v;                       break;
		case 20: tran.order.size.y = v;                       break;
		case 21: tran.order.TimeLimit = v;                       break;
		case 22: tran.order.repopTime = v;                       break;
		case 23:
			if (tran.order.金額.empty())  tran.order.金額.push_back(v);
			else                          tran.order.金額[0] = v;
			break;

		default:
			// それ以外の行は無視
			break;
		}
	}

	return true;
}

bool Transfer::SaveTransferToCsv(const std::string& path)
{
	TRAN_INS;

	const std::string tempPath = path + ".tmp";

	std::ifstream in(path);
	if (!in.is_open()) {
		return false;
	}

	std::ofstream out(tempPath);
	if (!out.is_open()) {
		return false;
	}

	std::string line;
	size_t row = 0;

	while (std::getline(in, line)) {
		++row;

		auto cells = SplitCsvLine(line, ',');

		if (cells.size() >= 4 && row >= 2) { // 2行目以降で数値列がある行だけ上書き候補
			float v;
			bool hasValue = true;

			switch (row)
			{
			case 2:  v = tran.player.pos.x;        break;
			case 3:  v = tran.player.pos.y;        break;
			case 4:  /* 未使用ならそのまま */     hasValue = false;   break;
			case 5:  v = tran.player.maxSpeed.x;   break; // x基準。yも同じにしている前提
			case 6:  v = tran.player.velocity;     break;

			case 7:  v = static_cast<float>(tran.stage.column); break;
			case 8:  v = static_cast<float>(tran.stage.row);    break;

			case 9:  v = tran.camera.eyePos.x;     break;
			case 10: v = tran.camera.eyePos.y;     break;
			case 11: v = tran.camera.eyePos.z;     break;

			case 12: v = tran.camera.lookPos.x;    break;
			case 13: v = tran.camera.lookPos.y;    break;
			case 14: v = tran.camera.lookPos.z;    break;

			case 15: v = tran.item.downSpeed;      break;
			case 16: v = tran.item.size.x;         break;
			case 17: v = tran.item.size.y;         break;
			case 18: v = tran.item.size.z;         break;

			case 19: v = tran.order.size.x;        break;
			case 20: v = tran.order.size.y;        break;
			case 21: v = tran.order.TimeLimit;     break;
			case 22: v = tran.order.repopTime;     break;
			case 23:
				if (!tran.order.金額.empty()) v = tran.order.金額[0];
				else                          hasValue = false;
				break;

			default:
				hasValue = false;
				break;
			}

			if (hasValue) {
				std::ostringstream oss;
				oss << v;              // 必要なら fixed << setprecision(3) とかでフォーマット
				cells[3] = oss.str();  // ★ 4列目だけ上書き
			}
		}

		out << JoinCsvLine(cells, ',') << "\n";
	}

	in.close();
	out.close();

	// 元ファイルと差し替え
	std::remove(path.c_str());
	if (std::rename(tempPath.c_str(), path.c_str()) != 0) {
		return false;
	}

	return true;
}