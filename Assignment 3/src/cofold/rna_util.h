#ifndef ACCURACY_H
#define ACCURACY_H

#include <vector>
#include <string>



int count_true_positives (const std::vector<int>& matching_true, const std::vector<int>& matching_proband)
{
	unsigned tps = 0;
	std::vector<bool> marked (matching_true.size(), false);

	for (int i = 0; i < matching_true.size(); ++i)
	{
		if (marked[i])
			continue;
		if (matching_true[i] != -1 && matching_true[i] == matching_proband[i])
		{
			tps += 1;
			marked[matching_true[i]] = true;
		}
	}
	return tps;
}

int count_false_negatives (const std::vector<int>& matching_true, const std::vector<int>& matching_proband)
{
	unsigned fns = 0;
	std::vector<bool> marked (matching_true.size(), false);

	for (int i = 0; i < matching_true.size(); ++i)
	{
		if (marked[i])
			continue;
		if (matching_true[i] != -1 && matching_proband[i] == -1)
		{
			fns += 1;
			marked[matching_true[i]] = true;
		}
	}
	return fns;
}

int count_false_positives (const std::vector<int>& matching_true, const std::vector<int>& matching_proband)
{
	unsigned fps = 0;
	std::vector<bool> marked (matching_true.size(), false);

	for (int i = 0; i < matching_true.size(); ++i)
	{
		if (marked[i])
			continue;
		if (matching_proband[i] != -1 && matching_true[i] != matching_proband[i])
		{
			fps += 1;
			marked[matching_proband[i]] = true;
		}
	}
	return fps;
}

float calc_sensitivity (const std::string& target, const std::string& prediction)
{
	std::vector<int> mtrue = get_matching_bonds (target);
	std::vector<int> mpred = get_matching_bonds (prediction); 
	float tp = count_true_positives (mtrue, mpred);
	float fn = count_false_negatives (mtrue, mpred);
	if (tp <= 0.0) return 0.0;
	return tp / (tp + fn);
}

float calc_ppv (const std::string& target, const std::string& prediction)
{
	std::vector<int> mtrue = get_matching_bonds (target);
	std::vector<int> mpred = get_matching_bonds (prediction); 
	float tp = count_true_positives (mtrue, mpred);
	float fp = count_false_positives (mtrue, mpred);
	if (tp <= 0.0) return 0.0;
	return tp / (tp + fp);
}

float calc_f1score (const std::string& target, const std::string& prediction)
{
	std::vector<int> mtrue = get_matching_bonds (target);
	std::vector<int> mpred = get_matching_bonds (prediction);
	float tp = count_true_positives (mtrue, mpred);
	float fp = count_false_positives (mtrue, mpred);
	float fn = count_false_negatives (mtrue, mpred);
	return (2 * tp) / (2 * tp + fp + fn);
}


int count_errors(const std::string& model, const std::string& proband)
{
	int count = 0;
	for(int i = 0; i < model.size(); ++i)
		if(model[i] != proband[i])
			++count;
	return count;
}



#endif