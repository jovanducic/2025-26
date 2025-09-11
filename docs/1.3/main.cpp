#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void tokenize(const string& str,
              vector<string>& tokens,
              const string& delimiters = " ") {
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  string::size_type pos     = str.find_first_of(delimiters, lastPos);

  while (string::npos != pos || string::npos != lastPos) {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, lastPos);
  }
}

vector<string> days;
vector<string> hours;
vector<string> groups;
vector<string> teachers;
map<string, vector< pair<string, string> > > subjects;

void generate_implications(string teacher, string group, string subject, int duration) {
  cout << "// tgs'd ... tgs'd" << endl;
  for (int day = 0; day < days.size(); day++) {
    cout << teacher << "_" << group << "_" << subject << "'" << "_" << days[day] << " ";
  }
  cout << endl;

  cout << "// tgs'd <=> tgs'dh ... tgs'dh" << endl;
  for (int day = 0; day < days.size(); day++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      cout << "-" << teacher << "_" << group << "_" << subject << "'" << "_" << days[day] << "_" << hours[hour] << " ";
      cout << teacher << "_" << group << "_" << subject << "'" << "_" << days[day] << endl;
    }

    cout << "-" << teacher << "_" << group << "_" << subject << "'" << "_" << days[day] << " ";
    for (int hour = 0; hour + duration - 1 < hours.size(); hour++) {
      cout << teacher << "_" << group << "_" << subject << "'" << "_" << days[day] << "_" << hours[hour] << " ";
    }
    cout << endl;
  }

  cout << "// tgsdh <=> tgs'dh ... tgs'dh" << endl;
  for (int day = 0; day < days.size(); day++) {
    for (int start_hour = 0; start_hour + duration - 1< hours.size(); start_hour++) {
      for (int hour = start_hour; hour < start_hour + duration; hour++) {
	cout << "-" << teacher << "_" << group << "_" << subject << "'" << "_" << days[day] << "_" << hours[start_hour] << " ";
	cout << teacher << "_" << group << "_" << subject << "_" << days[day] << "_" << hours[hour] << endl;
      }
    }

    for (int hour = 0; hour < hours.size(); hour ++ ) {
      cout << "-" << teacher << "_" << group << "_" << subject << "_" << days[day] << "_" << hours[hour] << " ";
      for (int start_hour = max(hour - duration + 1, 0); start_hour <= hour && start_hour + duration << hours.size(); start_hour++) {
	cout << teacher << "_" << group << "_" << subject << "'" << "_" << days[day] << "_" << hours[start_hour] << " ";
      }
      cout << endl;
    }
  }
}


void generate_implications() {
  cout << "// td <=> tdh ... tdh " << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size(); hour++) {
	cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[hour] << " ";
	cout << teachers[teacher] << "_" << days[day] << endl;
      }

      cout << "-" << teachers[teacher] << "_" << days[day] << " ";
      for (int hour = 0; hour < hours.size(); hour++) {
	cout << teachers[teacher] << "_" << days[day] << "_" << hours[hour] << " ";
      }
      cout << endl;
    }
  }

  cout << "// th <=> tdh ... tdh " << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      for (int day = 0; day < days.size(); day++) {
	cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[hour] << " ";
	cout << teachers[teacher] << "_" << hours[hour] << endl;
      }

      cout << "-" << teachers[teacher] << "_" << hours[hour] << " ";
      for (int day = 0; day < days.size(); day++) {
	cout << teachers[teacher] << "_" << days[day] << "_" << hours[hour] << " ";
      }
      cout << endl;
    }
  }

  cout << "// gh <=> gdh ... gdh " << endl;
  for (int group = 0; group < groups.size(); group++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      for (int day = 0; day < days.size(); day++) {
	cout << "-" << groups[group] << "_" << days[day] << "_" << hours[hour] << " ";
	cout << groups[group] << "_" << hours[hour] << endl;
      }

      cout << "-" << groups[group] << "_" << hours[hour] << " ";
      for (int day = 0; day < days.size(); day++) {
	cout << groups[group] << "_" << days[day] << "_" << hours[hour] << " ";
      }
      cout << endl;
    }
  }

  cout << "// gd <=> gdh ... gdh " << endl;
  for (int group = 0; group < groups.size(); group++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size(); hour++) {
	cout << "-" << groups[group] << "_" << days[day] << "_" << hours[hour] << " ";
	cout << groups[group] << "_" << days[day] << endl;
      }

      cout << "-" << groups[group] << "_" << days[day] << " ";
      for (int hour = 0; hour < hours.size(); hour++) {
	cout << groups[group] << "_" << days[day] << "_" << hours[hour] << " ";
      }
      cout << endl;
    }
  }

  cout << "// tdh <=> tgsdh ... tgsdh" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size(); hour++) {
	for (int i = 0; i < subjects[teachers[teacher]].size(); i++) {
	  cout << "-" << teachers[teacher] << "_" << subjects[teachers[teacher]][i].first << "_" << subjects[teachers[teacher]][i].second << "_" << days[day] << "_" << hours[hour] << " ";
	  cout << teachers[teacher] << "_" << days[day] << "_" << hours[hour] << endl;
	}

	cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[hour] << " ";
	for (int i = 0; i < subjects[teachers[teacher]].size(); i++) {
	  cout << teachers[teacher] << "_" << subjects[teachers[teacher]][i].first << "_" << subjects[teachers[teacher]][i].second << "_" << days[day] << "_" << hours[hour] << " ";
	}
	cout << endl;
      }
    }
  }


  cout << "// td <=> tgs'd ... tgs'd" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      for (int i = 0; i < subjects[teachers[teacher]].size(); i++) {
	cout << "-" << teachers[teacher] << "_" << subjects[teachers[teacher]][i].first << "_" << subjects[teachers[teacher]][i].second << "'_" << days[day] << " ";
	cout << teachers[teacher] << "_" << days[day] << endl;
      }

      cout << "-" << teachers[teacher] << "_" << days[day] << " ";
      for (int i = 0; i < subjects[teachers[teacher]].size(); i++) {
	cout << teachers[teacher] << "_" << subjects[teachers[teacher]][i].first << "_" << subjects[teachers[teacher]][i].second << "'_" << days[day] << " ";
      }
      cout << endl;
    }
  }

  cout << "// gdh <=> tgsdh ... tgsdh" << endl;
  for (int group = 0; group < groups.size(); group++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size(); hour++) {
	for (int i = 0; i < subjects[groups[group]].size(); i++) {
	  cout << "-" << subjects[groups[group]][i].first << "_" << groups[group] << "_" << subjects[groups[group]][i].second << "_" << days[day] << "_" << hours[hour] << " ";
	  cout << groups[group] << "_" << days[day] << "_" << hours[hour] << endl;
	}

	cout << "-" << groups[group] << "_" << days[day] << "_" << hours[hour] << " ";
	for (int i = 0; i < subjects[groups[group]].size(); i++) {
	  cout << subjects[groups[group]][i].first << "_" << groups[group] << "_" << subjects[groups[group]][i].second << "_" << days[day] << "_" << hours[hour] << " ";;
	}
	cout << endl;
      }
    }
  }

  cout << "// t'dh <=> tgs'dh ... tgs'dh" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size(); hour++) {
	for (int i = 0; i < subjects[teachers[teacher]].size(); i++) {
	  cout << "-" << teachers[teacher] << "_" << subjects[teachers[teacher]][i].first << "_" << subjects[teachers[teacher]][i].second << "'_" << days[day] << "_" << hours[hour] << " ";
	  cout << teachers[teacher] << "'_" << days[day] << "_" << hours[hour] << endl;
	}

	cout << "-" << teachers[teacher] << "'_" << days[day] << "_" << hours[hour] << " ";
	for (int i = 0; i < subjects[teachers[teacher]].size(); i++) {
	  cout << teachers[teacher] << "_" << subjects[teachers[teacher]][i].first << "_" << subjects[teachers[teacher]][i].second << "'_" << days[day] << "_" << hours[hour] << " ";
	}
	cout << endl;
      }
    }
  }
}


// unique(tgs'dh)
void generate_unique_occurence_condition(string teacher, string group, string subject_start) {
  cout << "// each class is held exactly once" << endl;
  for (int day1 = 0; day1 < days.size(); day1++) {
    for (int day2 = day1+1; day2 < days.size(); day2++) {
      cout << "-" << teacher << "_" << group << "_" << subject_start << "_" << days[day1] << " ";
      cout << "-" << teacher << "_" << group << "_" << subject_start << "_" << days[day2] << endl;
    }
  }

  for (int day = 0; day < days.size(); day++) {
    for (int hour1 = 0; hour1 < hours.size(); hour1++) {
      for (int hour2 = hour1 + 1; hour2 < hours.size(); hour2++) {
	cout << "-" << teacher << "_" << group << "_" << subject_start << "_" << days[day] << "_" << hours[hour1] << " ";
	cout << "-" << teacher << "_" << group << "_" << subject_start << "_" << days[day] << "_" << hours[hour2] << endl;
      }
    }
  }
}

void generate_distinct_day_conditions(string teacher, string group, string subject, int cday) {
  cout << "// distinct_day" << endl;
  for (int day1 = 0; day1 < days.size(); day1++) {
    if (day1 == 0) {
      cout << "-" << teacher << "_" << group << "_" << subject << "." << cday + 1 << "'_" << days[day1] << endl;
    } else if (day1 == days.size() - 1) {
      cout << "-" << teacher << "_" << group << "_" << subject << "." << cday << "'_" << days[day1] << endl;
    } else {
      for (int day2 = 0; day2 <= day1; day2++) {
	cout << "-" << teacher << "_" << group << "_" << subject << "." << cday << "'_" << days[day1] << " ";
	cout << "-" << teacher << "_" << group << "_" << subject << "." << cday + 1 << "'_" << days[day2] << endl;
      }
    }
  }
}

void generate_conditions(string teacher, string group, string subject, string classes, bool group_representative) {
  vector<string> class_days;
  tokenize(classes, class_days, ",");

  for (int cday = 0; cday < class_days.size(); cday++) {
    int duration = atoi(class_days[cday].c_str());
    string subject_day = subject + "." + to_string(cday + 1);
    generate_unique_occurence_condition(teacher, group, subject_day + "'");
    generate_implications(teacher, group, subject_day, duration);
    if (cday >= 1)
      generate_distinct_day_conditions(teacher, group, subject, cday);
    subjects[group].push_back(pair<string, string>(teacher, subject_day));
    if (group_representative)
      subjects[teacher].push_back(pair<string, string>(group, subject_day));
  }
}

void addTeacher(string teacher) {
  if (find(teachers.begin(), teachers.end(), teacher) == teachers.end())
    teachers.push_back(teacher);
}

void addGroup(string group) {
  if (find(groups.begin(), groups.end(), group) == groups.end())
    groups.push_back(group);
}


void generate_same_time_conditions(string o1, string o2) {
  for (int day = 0; day < days.size(); day++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      cout << "-" << o1 << "_" << days[day] << "_" << hours[hour] << " ";
      cout << o2 << "_" << days[day] << "_" << hours[hour] <<  endl;

      cout << "-" << o2 << "_" << days[day] << "_" << hours[hour] << " ";
      cout << o1 << "_" << days[day] << "_" << hours[hour] <<  endl;
    }
  }
}

void generate_same_time_conditions(string teacher, const vector<string>& groups, string subject) {
  cout << "// same time" << endl;
  for (int group1 = 0; group1 < groups.size(); group1++) {
    for (int group2 = group1 + 1; group2 < groups.size(); group2++) {
      generate_same_time_conditions(teacher + "_" + groups[group1] + "_" + subject,
				    teacher + "_" + groups[group2] + "_" + subject);
    }
  }
}

void generate_same_time_conditions(string teacher, const vector<string>& groups, string subject, string classes) {
  vector<string> class_days;
  tokenize(classes, class_days, ",");

  for (int cday = 0; cday < class_days.size(); cday++) {
    string subject_day = subject + "." + to_string(cday + 1);
    generate_same_time_conditions(teacher, groups, subject_day + "'");
  }
}


void generate_unique_group_conditions() {
  cout << "//unique group" << endl;
  for (int group = 0; group < groups.size(); group++) {
    for (int i1 = 0; i1 < subjects[groups[group]].size(); i1++) {
      for (int i2 = i1+1; i2 < subjects[groups[group]].size(); i2++) {
	for (int day = 0; day < days.size(); day++) {
	  for (int hour = 0; hour < hours.size(); hour++) {
            // francuski i ruski smeju istovremeno
            if ((subjects[groups[group]][i1].second.rfind("fra", 0) == 0 && subjects[groups[group]][i2].second.rfind("rus", 0) == 0) ||
                (subjects[groups[group]][i1].second.rfind("rus", 0) == 0 && subjects[groups[group]][i2].second.rfind("fra", 0) == 0))
              continue;
            // gradjansko i veronauka smeju istovremeno
            if ((subjects[groups[group]][i1].second.rfind("gra", 0) == 0 && subjects[groups[group]][i2].second.rfind("ver", 0) == 0) ||
                (subjects[groups[group]][i1].second.rfind("ver", 0) == 0 && subjects[groups[group]][i2].second.rfind("gra", 0) == 0))
              continue;
            // vezbanjem do zdravlja i medijska pismenost smaju istovremeno
            if ((subjects[groups[group]][i1].second.rfind("vdz", 0) == 0 && subjects[groups[group]][i2].second.rfind("mp") == 0) ||
                (subjects[groups[group]][i1].second.rfind("mp", 0) == 0 && subjects[groups[group]][i2].second.rfind("vdz", 0) == 0))
              continue;
            // cuvari prirode i medijska pismenost smeju istovremeno
            if ((subjects[groups[group]][i1].second.rfind("cp", 0) == 0 && subjects[groups[group]][i2].second.rfind("mp", 0) == 0) ||
                (subjects[groups[group]][i1].second.rfind("mp", 0) == 0 && subjects[groups[group]][i2].second.rfind("cp", 0) == 0))
              continue;
            // cuvari prirode i zivotne vestine smeju istovremeno
            if ((subjects[groups[group]][i1].second.rfind("cp", 0) == 0 && subjects[groups[group]][i2].second.rfind("zv", 0) == 0) ||
                (subjects[groups[group]][i1].second.rfind("zv", 0) == 0 && subjects[groups[group]][i2].second.rfind("cp", 0) == 0))
              continue;
            // medijska pismenost i zivotne vestine smeju istovremeno
            if ((subjects[groups[group]][i1].second.rfind("mp", 0) == 0 && subjects[groups[group]][i2].second.rfind("zv", 0) == 0) ||
                (subjects[groups[group]][i1].second.rfind("zv", 0) == 0 && subjects[groups[group]][i2].second.rfind("mp", 0) == 0))
              continue;
            // umetnost i moja zivotna sredina smeju istovremeno
            if ((subjects[groups[group]][i1].second.rfind("mzs", 0) == 0 && subjects[groups[group]][i2].second.rfind("um", 0) == 0) ||
                (subjects[groups[group]][i1].second.rfind("um", 0) == 0 && subjects[groups[group]][i2].second.rfind("mzs", 0) == 0))
              continue;

	    cout << "-" << subjects[groups[group]][i1].first << "_" << groups[group] << "_" << subjects[groups[group]][i1].second << "_" << days[day] << "_" << hours[hour] << " ";
	    cout << "-" << subjects[groups[group]][i2].first << "_" << groups[group] << "_" << subjects[groups[group]][i2].second << "_" << days[day] << "_" << hours[hour] << endl;
	  }
	}
      }
    }
  }
}

void generate_unique_teacher_conditions() {
  cout << "//unique teacher" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int i1 = 0; i1 < subjects[teachers[teacher]].size(); i1++) {
      for (int i2 = i1+1; i2 < subjects[teachers[teacher]].size(); i2++) {
	for (int day = 0; day < days.size(); day++) {
	  for (int hour = 0; hour < hours.size(); hour++) {
	    cout << "-" << teachers[teacher] << "_" << subjects[teachers[teacher]][i1].first << "_" << subjects[teachers[teacher]][i1].second << "_" << days[day] << "_" << hours[hour] << " ";
	    cout << "-" << teachers[teacher] << "_" << subjects[teachers[teacher]][i2].first << "_" << subjects[teachers[teacher]][i2].second << "_" << days[day] << "_" << hours[hour] << endl;
	  }
	}
      }
    }
  }
}

void generate_long_stay_conditions() {
  int max_duration = 7;
  for (int group = 0; group < groups.size(); group++) {
    for (int day = 0; day < days.size(); day++) {
      for (int i = 0; i + max_duration < hours.size(); i++) {
	for (int j = i + max_duration; j < hours.size(); j++) {
	  cout << "-" << groups[group] << "_" << days[day] << "_" << hours[i] << " ";
	  cout << "-" << groups[group] << "_" << days[day] << "_" << hours[j] << endl;
	}
      }
    }
  }

  max_duration = 6;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      for (int d = 2; d <= hours.size(); d++) {
	for (int i = 0; i + d - 1 < hours.size(); i++) {
	  cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[i] << " ";
	  cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[i+d-1] << " ";
	  cout << teachers[teacher] << "_" << "duration" << "_" << days[day] << "_" << d << endl;
	}
      }

      // biologicarka mora u dva dana
      if (teachers[teacher] == "miiv") continue;
      // veroucitelj
      if (teachers[teacher] == "pone") continue;
      if (teachers[teacher] == "rejo") continue;

      for (int d = max_duration + 1; d <= hours.size(); d++) {
	cout << "-" << teachers[teacher] << "_" << "duration" << "_" << days[day] << "_" << d << endl;
      }
    }
  }

  // min_duration
  cout << "// min_duration" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    // dopusten samo 1 cas
    if (teachers[teacher] == "pone")
      continue;
    if (teachers[teacher] == "busne")
      continue;

    for (int day = 0; day < days.size(); day++) {
      // cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[0] << " ";
      // cout << teachers[teacher] << "_" << days[day] << "_" << hours[1] << endl;

      // Izmena u odnosu na prethodnu varijantu: dopuštena pauza drugi čas
      cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[0] << " ";
      cout << teachers[teacher] << "_" << days[day] << "_" << hours[1] << " ";
      cout << teachers[teacher] << "_" << days[day] << "_" << hours[2] << endl;

      for (int h = 1; h < hours.size() - 1; h++) {
	if (teachers[teacher] == "busne") continue;
	cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[h] << " ";
	cout << teachers[teacher] << "_" << days[day] << "_" << hours[h-1] << " ";
	cout << teachers[teacher] << "_" << days[day] << "_" << hours[h+1] << endl;
      }

      // cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[hours.size() - 1] << " ";
      // cout << teachers[teacher] << "_" << days[day] << "_" << hours[hours.size() - 2] << endl;

      // Izmena u odnosu na prethodnu varijantu: dopuštena pauza pretposlednji čas
      cout << "-" << teachers[teacher] << "_" << days[day] << "_" << hours[hours.size() - 1] << " ";
      cout << teachers[teacher] << "_" << days[day] << "_" << hours[hours.size() - 2] << " ";
      cout << teachers[teacher] << "_" << days[day] << "_" << hours[hours.size() - 3] << endl;

    }
  }

  // zabranjeno 7 casova bez pauze
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    // biologicarka mora u dva dana
    if (teachers[teacher] == "miiv") continue;
    // veronauka
    if (teachers[teacher] == "pone") continue;
    // cos
    if (teachers[teacher] == "somi") continue;


    for (int day = 0; day < days.size(); day++) {
      cout << "-" << teachers[teacher] << "_" << "duration" << "_" << days[day] << "_" << 7 << " ";
      for (int h = 3; h <= 5; h++)
	cout << teachers[teacher] << "_" << "hole1" << "_" << days[day] << "_" <<  h << " ";
      cout << endl;
    }
  }
}

void generate_distinct_group_conditions(const vector<string>& dg) {
  cout << "// distinct groups " << endl;
  for (int day = 0; day < days.size(); day++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      for (int g = 0; g < dg.size(); g++) {
	cout << "-" << dg[g] << "_" << days[day] << "_" << hours[hour] << " ";
      }
      cout << endl;
    }
  }
}

void generate_hole_conditions() {
  for (int h = 1; h < hours.size() - 1; h++) {
    cout << "// hole" << h << endl;

    for (int teacher = 0; teacher < teachers.size(); teacher++) {
      for (int day = 0; day < days.size(); day++) {
	int k, m;
	for (k = 0; k < hours.size() - 1 - h; k++) {
	  cout << teachers[teacher] << "_" << "hole" << h << " ";
	  for (m = 0; m < h + 2; m++) {
	    cout << ((m != 0 && m != h + 1) ? "" : "-") << teachers[teacher] << "_" << days[day] << "_" << hours[k+m] << " ";
	  }
	  cout << endl;
	}
      }
    }
    for (int group = 0; group < groups.size(); group++) {
      for (int day = 0; day < days.size(); day++) {
	int k, m;
	for (k = 0; k < hours.size() - 1 - h; k++) {
	  cout << groups[group] << "_" << "hole" << h << " ";
	  for (m = 0; m < h + 2; m++) {
	    cout << ((m != 0 && m != h + 1) ? "" : "-") << groups[group] << "_" << days[day] << "_" << hours[k+m] << " ";
	  }
	  cout << endl;
	}
      }
    }
  }

  cout << "// hole1_d_c" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size() - 2; hour++) {
	cout << teachers[teacher] << "_" << "hole1_" << days[day] << "_" << hours[hour + 1] << " ";
	for (int m = 0; m < 3; m++) {
	  cout << ((m == 1) ? "" : "-") << teachers[teacher] << "_" << days[day] << "_" << hours[hour + m] << " ";
	}
	cout << endl;

	for (int m = 0; m < 3; m++) {
	  cout << "-" << teachers[teacher] << "_" << "hole1_" << days[day] << "_" << hours[hour + 1] << " ";
	  cout << ((m == 1) ? "-" : "") << teachers[teacher] << "_" << days[day] << "_" << hours[hour + m] << endl;
	}
      }
    }
  }

  cout << "// hole1_d" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      cout << "-" << teachers[teacher] << "_" << "hole1_" << days[day] << " ";
      for (int hour = 1; hour < hours.size()-1; hour++)
        cout << teachers[teacher] << "_" << "hole1_" << days[day] << "_" << hours[hour] << " ";
      cout << endl;

      for (int hour = 1; hour < hours.size()-1; hour++) {
        cout << "-" << teachers[teacher] << "_" << "hole1_" << days[day] << "_" << hours[hour] << " ";
        cout << teachers[teacher] << "_" << "hole1_" << days[day] << endl;
      }
    }    
  }  

  for (int group = 0; group < groups.size(); group++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size() - 2; hour++) {
	cout << groups[group] << "_" << "hole1_" << days[day] << "_" << hours[hour + 1] << " ";
	for (int m = 0; m < 3; m++) {
	  cout << ((m == 1) ? "" : "-") << groups[group] << "_" << days[day] << "_" << hours[hour + m] << " ";
	}
	cout << endl;
      }
    }
  }

  cout << "// hole2_d_c" << endl;
  for (int group = 0; group < groups.size(); group++) {
    for (int day = 0; day < days.size(); day++) {
      for (int hour = 0; hour < hours.size() - 3; hour++) {
	cout << groups[group] << "_" << "hole2_" << days[day] << "_" << hours[hour + 1] << " ";
	for (int m = 0; m < 4; m++) {
	  cout << ((m == 1 || m == 2) ? "" : "-") << groups[group] << "_" << days[day] << "_" << hours[hour + m] << " ";
	}
	cout << endl;
      }
    }
  }

  cout << "// 2hole1_same_day" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day = 0; day < days.size(); day++) {
      int k, m;
      for (k = 1; k < hours.size() - 1; k++) {
	for (m = k + 2; m < hours.size() - 1; m++) {
	  cout << "-" << teachers[teacher] << "_" << "hole1_" << days[day] << "_" << hours[k] << " ";
	  cout << "-" << teachers[teacher] << "_" << "hole1_" << days[day] << "_" << hours[m] << " ";
	  cout << teachers[teacher] << "_" << "2hole1_same_day" << endl;
	}
      }
    }
  }

  cout << "// 2hole1" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    int k, m, n;
    int a = hours.size() - 2;
    int b = days.size();
    for (k = 0; k < a*b; k++) {
      for (m = k+1; m < a*b; m++) {
	cout << "-" << teachers[teacher] << "_" << "hole1_" << days[k / a] << "_" << hours[(k % a) + 1] << " ";
	cout << "-" << teachers[teacher] << "_" << "hole1_" << days[m / a] << "_" << hours[(m % a) + 1] << " ";
	cout << teachers[teacher] << "_" << "2hole1" << endl;
      }
    }
  }

  for (int group = 0; group < groups.size(); group++) {
    int k, m, n;
    int a = hours.size() - 2;
    int b = days.size();
    for (k = 0; k < a*b; k++) {
      for (m = k+1; m < a*b; m++) {
	cout << "-" << groups[group] << "_" << "hole1_" << days[k / a] << "_" << hours[(k % a) + 1] << " ";
	cout << "-" << groups[group] << "_" << "hole1_" << days[m / a] << "_" << hours[(m % a) + 1] << " ";
	cout << groups[group] << "_" << "2hole1" << endl;
      }
    }
  }


  cout << "// 2hole2" << endl;
  for (int group = 0; group < groups.size(); group++) {
    int k, m, n;
    int a = hours.size() - 3;
    int b = days.size();
    for (k = 0; k < a*b; k++) {
      for (m = k+1; m < a*b; m++) {
	cout << "-" << groups[group] << "_" << "hole2_" << days[k / a] << "_" << hours[(k % a) + 1] << " ";
	cout << "-" << groups[group] << "_" << "hole2_" << days[m / a] << "_" << hours[(m % a) + 1] << " ";
	cout << groups[group] << "_" << "2hole2" << endl;
      }
    }
  }

  cout << "// no 3 days with hole1" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    for (int day1 = 0; day1 < days.size(); day1++)
      for (int day2 = day1+1; day2 < days.size(); day2++)
        for (int day3 = day2+1; day3 < days.size(); day3++)
          cout << "-" << teachers[teacher] << "_" << "hole1_" << days[day1] << " "
               << "-" << teachers[teacher] << "_" << "hole1_" << days[day2] << " "
               << "-" << teachers[teacher] << "_" << "hole1_" << days[day3] << endl;
  }

  for (int h = 1; h < hours.size() - 1; h++) {
    for (int teacher = 0; teacher < teachers.size(); teacher++) {
      if (teachers[teacher] == "pone") continue;
      if (teachers[teacher] == "busne") continue;
      if (teachers[teacher] == "trina") continue;
      if (h > 1) {
	cout << "-" << teachers[teacher] << "_" << "hole" << h << endl;
      }
    }

    for (int group = 0; group < groups.size(); group++) {
      if (h > 0)
	cout << "-" << groups[group] << "_" << "hole" << h << endl;
    }
  }

  for (int group = 0; group < groups.size(); group++) {
    cout << "-" << groups[group] << "_" << "2hole1" << endl;
    cout << "-" << groups[group] << "_" << "2hole2" << endl;
  }

  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    //    cout << "-" << teachers[teacher] << "_" << "2hole1" << endl;
    cout << "-" << teachers[teacher] << "_" << "2hole2" << endl;
  }
}


void generate_number_of_days_conditions(const vector<string>& teachers) {
  int day, day1;
  cout << "// p works exactly 1 day" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    // p_1day <=> p_1day_pon \/ p_1day_uto \/ p_1day_sre \/ p_1day_cet \/ p_1day_pet
    cout << "-" << teachers[teacher] << "_1day ";
    for (day = 0; day < days.size(); day++) {
      cout << teachers[teacher] << "_1day_" << days[day] << " ";
    }
    cout << endl;

    for (day = 0; day < days.size(); day++) {
      cout << "-" << teachers[teacher] << "_1day_" << days[day] << " ";
      cout << teachers[teacher] << "_1day ";
      cout << endl;
    }

    // p_1day_d <=> /\-p_di /\ p_d
    for (day1 = 0; day1 < days.size(); day1++) {
      for (day = 0; day < days.size(); day++) {
	cout << "-" << teachers[teacher] << "_1day_" << days[day1] << " ";
	cout << (day == day1 ? "" : "-") << teachers[teacher] << "_" << days[day] << endl;
      }
      cout << teachers[teacher] << "_1day_" << days[day1] << " ";

      for (day = 0; day < days.size(); day++) {
	cout << (day == day1 ? "-" : "") << teachers[teacher] << "_" << days[day] << " ";
      }
      cout << endl;
    }
  }
  cout << endl;

  cout << "// p works exactly 2 days" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    // p_2day <=> p_2day_ponuto \/ p_1day_ponsre \/ ... \/ p_1day_cetpet
    cout << "-" << teachers[teacher] << "_2day ";
    for (int day1 = 0; day1 < days.size(); day1++) {
      for (int day2 = day1+1; day2 < days.size(); day2++) {
	cout << teachers[teacher] << "_2day_" << days[day1] << days[day2] << " ";
      }
    }
    cout << endl;

    for (int day1 = 0; day1 < days.size(); day1++) {
      for (int day2 = day1+1; day2 < days.size(); day2++) {
	cout << "-" << teachers[teacher] << "_2day_" << days[day1] << days[day2] << " ";
	cout << teachers[teacher] << "_2day ";
	cout << endl;
      }
    }

    // p_2day_d1d2 <=> /\-p_di /\ p_d1 /\ pd2
    for (int day1 = 0; day1 < days.size(); day1++) {
      for (int day2 = day1+1; day2 < days.size(); day2++) {
	for (int day = 0; day < days.size(); day++) {
	  cout << "-" << teachers[teacher] << "_2day_" << days[day1] << days[day2] << " ";  
	  cout << ((day == day1 || day == day2) ? "" : "-") << teachers[teacher] << "_" << days[day] << " ";
	  cout << endl;
	}

	cout << teachers[teacher] << "_2day_" << days[day1] << days[day2] << " ";
	for (int day = 0; day < days.size(); day++) {
	  cout << ((day == day1 || day == day2) ? "-" : "") << teachers[teacher] << "_" << days[day] << " ";
	}
	cout << endl;
      }
    }
  }

  cout << "// p works exactly 3 days" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    // p_3day <=> p_3day_ponuto \/ p_3day_ponsre \/ ... \/ p_3day_cetpet
    cout << "-" << teachers[teacher] << "_3day ";
    for (int day1 = 0; day1 < days.size(); day1++) {
      for (int day2 = day1+1; day2 < days.size(); day2++) {
	cout << teachers[teacher] << "_3day_" << days[day1] << days[day2] << " ";
      }
    }
    cout << endl;

    for (int day1 = 0; day1 < days.size(); day1++) {
      for (int day2 = day1+1; day2 < days.size(); day2++) {
	cout << "-" << teachers[teacher] << "_3day_" << days[day1] << days[day2] << " ";
	cout << teachers[teacher] << "_3day ";
	cout << endl;
      }
    }

    // p_3day_d1d2 <=> /\p_di /\ -p_d1 /\ -pd2
    for (int day1 = 0; day1 < days.size(); day1++) {
      for (int day2 = day1+1; day2 < days.size(); day2++) {
	for (int day = 0; day < days.size(); day++) {
	  cout << "-" << teachers[teacher] << "_3day_" << days[day1] << days[day2] << " ";  
	  cout << ((day == day1 || day == day2) ? "-" : "") << teachers[teacher] << "_" << days[day] << " ";
	  cout << endl;
	}

	cout << teachers[teacher] << "_3day_" << days[day1] << days[day2] << " ";
	for (int day = 0; day < days.size(); day++) {
	  cout << ((day == day1 || day == day2) ? "" : "-") << teachers[teacher] << "_" << days[day] << " ";
	}
	cout << endl;
      }
    }
  }


  cout << "// p works exactly 4 days" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    // p_4day <=> p_4day_pon \/ p_4day_uto \/ p_4day_sre \/ p_4day_cet \/ p_4day_pet
    cout << "-" << teachers[teacher] << "_4day ";
    for (day = 0; day < days.size(); day++) {
      cout << teachers[teacher] << "_4day_" << days[day] << " ";
    }
    cout << endl;

    for (day = 0; day < days.size(); day++) {
      cout << "-" << teachers[teacher] << "_4day_" << days[day] << " ";
      cout << teachers[teacher] << "_4day ";
      cout << endl;
    }

    // p_4day_d <=> /\p_di /\ -p_d
    for (day1 = 0; day1 < days.size(); day1++) {
      for (day = 0; day < days.size(); day++) {
	cout << "-" << teachers[teacher] << "_4day_" << days[day1] << " ";
	cout << (day == day1 ? "-" : "") << teachers[teacher] << "_" << days[day] << " ";
	cout << endl;
      }

      cout << teachers[teacher] << "_4day_" << days[day1] << " ";

      for (day = 0; day < days.size(); day++) {
	cout << (day == day1 ? "" : "-") << teachers[teacher] << "_" << days[day] << " ";
      }
      cout << endl;
    }
  }
  cout << endl;

  cout << "// p works exactly 5 days" << endl;
  for (int teacher = 0; teacher < teachers.size(); teacher++) {
    cout << teachers[teacher] << "_5day" << " ";
    for (day = 0; day < days.size(); day++) {
      cout << "-" << teachers[teacher] << "_" << days[day] << " ";
    }
    cout << endl;

    for (day = 0; day < days.size(); day++) {
      cout << "-" << teachers[teacher] << "_5day" << " ";
      cout << teachers[teacher] << "_" << days[day] << " ";
      cout << endl;
    }
  }
  cout << endl;
}

void generate_distinct_subject_group_conditions(string subject, string group) {
  for (int day = 0; day < days.size(); day++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      cout << "-" << subject << "_" << days[day] << "_" << hours[hour] << " ";
      cout << "-" << group << "_" << days[day] << "_" << hours[hour] << " ";
    }
  }
}

void generate_cardinality_constraints(const vector<string>& inputs, int k, string prefix, string suffix) {
  int n = inputs.size();
  prefix += "s_index.";

  cout << "// " << suffix << " " << k << endl;
  // write clauses of first partial sum (i.e. i=0)
  cout << "-" << inputs[0] << suffix << " ";
  cout << prefix << "0.0." << k << suffix << endl;

  for(int j=1; j < k; j++)
    cout << "-" << prefix << "0." << j << "." << k << suffix << endl;

  // write clauses for general case (i.e. 0 < i < n-1)
  for(int i=1; i < n-1; i++) {
    cout << "-" << inputs[i] << suffix << " ";
    cout << prefix << i << ".0." << k << suffix << endl;

    cout << "-" << prefix << i-1 << ".0." << k << suffix << " ";
    cout << prefix << i << ".0." << k << suffix << endl;

    for(int j=1; j < k; j++) {
      cout << "-" << inputs[i] << suffix << " ";
      cout << "-" << prefix << i-1 << "." << j-1 << "." << k << suffix << " ";
      cout << prefix << i << "." << j << "." << k << suffix << endl;

      cout << "-" << prefix << i-1 << "." << j << "." << k << suffix << " ";
      cout << prefix << i << "." << j << "." << k << suffix << endl;
    }

    cout << "-" << inputs[i] << suffix << " ";
    cout << "-" << prefix << i-1 << "." << k-1 << "." << k << suffix << endl;
  }

  // last clause for the last variable
  cout << "-" << inputs[n-1] << suffix << " ";
  cout << "-" << prefix << n-2 << "." << k-1 << "." << k << suffix << endl;
}

/*
  00 f   10 v              20
  01 0   11 01 + v + 00    21
  02 0   12 v + 01         22
*/
void generate_cardinality_constraints(const vector<string>& inputs, int k0, string prefix) {
  cout << "// cardinality constraints: " << k0 << " " << prefix <<  endl;
  for (int day = 0; day < days.size(); day++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      int k = (prefix == "_people_" && atoi(hours[hour].c_str()) >= 14) ? k0 - 1 : k0;
      string suffix = string("_") + days[day]  + string("_") + hours[hour];
      generate_cardinality_constraints(inputs, k, prefix, suffix);
    }
  }
}

  /* UMETNUTO */
string s_index(int i, int j, int k, string c, string additional) {
  if (i != k - 1)
    return string("s_id") + "." + to_string(i + 1) + "." + to_string(j + 1) + "__" + c + "_" + additional;
  else
    return string("cnt_") + additional + "_" + to_string(j + 1);
}


string neg(string input) {
  if (input[0] == '-')
    return input.substr(1);
  else
    return string("-") + input;
}


void generate_sequential_counter(const vector<string>& inputs, string additional, int k) {
  int n = inputs.size();

  cout << "// sequential_counter: " << n << " : " << k << endl;
  static int static_cnt;
  string c = to_string(static_cnt++);

  for(int i=0; i < n; i++) {
    for(int j=0; j <= i && j < k; j++) {
      // ui && s(i-1)(j-1) => sij
      cout << neg(inputs[i]) << " ";
      if (j > 0) {
	cout << "-" << s_index(i-1, j-1, n, c, additional) << " ";
      }
      cout << s_index(i, j, n, c, additional) << " ";
      cout << endl;

      if (j < i) {
	// s(i-1)j => sij
	cout << "-" << s_index(i-1, j, n, c, additional) << " ";
	cout << s_index(i, j, n, c, additional) << " ";
	cout << endl;
      }

      // sij => ui || s(i-1)j
      cout << "-" << s_index(i, j, n, c, additional) << " ";
      cout << inputs[i] << " ";
      if (j < i) {
	cout << s_index(i-1, j, n, c, additional) << " ";
      }
      cout << endl;

      if (j > 0) {
	// sij => s(i-1)(j-1)
	cout << "-" << s_index(i, j, n, c, additional) << " ";
	cout << s_index(i-1, j-1, n, c, additional) << " ";
	cout << endl;
      }
    }
  }
}

void generate_cardinality_constraints_new(const vector<string>& inputs, int k, string additional, string kosme) {
  generate_sequential_counter(inputs, additional, k+1);
  if (kosme != "") {
    cout << "-" << string("cnt_") + additional + "_" + to_string(k) << kosme << endl;;
  }
  cout << "-" << string("cnt_") + additional + "_" + to_string(k + 1) << endl;;
}

void generate_cardinality_constraints_for_each_time(const vector<string>& inputs, int k, string additional) {
  for (int day = 0; day < days.size(); day++) {
    for (int hour = 0; hour < hours.size(); hour++) {
      vector<string> inputs_dh;
      for (int i = 0; i < inputs.size(); i++)
	inputs_dh.push_back(inputs[i] + "_" + days[day] + "_" + hours[hour]);
      string suffix = string("_")  + days[day] + string("_") + hours[hour];
      string i5 = additional == "_tch_" ? string(" 5i")+suffix : string("");
      generate_cardinality_constraints_new(inputs_dh, k, additional + suffix, i5);
    }
  }
}

/* KRAJ UMETNUTO */

void generate_afternoon_conditions() {
  cout << "// afternoon" << endl;
  for (int group = 0; group < groups.size(); group++) {
    for (int day = 0; day < days.size(); day++) {
      int hour;
      for (hour = 0; hour < hours.size()/2; hour++) {
	cout << "-" << groups[group] << "_" << "free_morning_" << days[day] << " ";
	cout << "-" << groups[group] << "_" << days[day] << "_" << hours[hour] << endl;
      }
      for (; hour < hours.size(); hour++) {
	cout << "-" << groups[group] << "_" << "free_afternoon_" << days[day] << " ";
	cout << "-" << groups[group] << "_" << days[day] << "_" << hours[hour] << endl;
      }
    }
  }
}

void parse() {
  int room_card = 0;
  string line;
  while(getline(cin, line)) {
    if (line == "days") {
      getline(cin, line);
      tokenize(line, days, "\t");
    } else if (line == "hours") {
      getline(cin, line);
      tokenize(line, hours, "\t");
    } else if (line == "distinct") {
      while (1) {
	getline(cin, line);
	if (line == "") break;
	vector<string> dg;
	tokenize(line, dg, "\t");
	generate_distinct_group_conditions(dg);
      }
    } else if (line == "same_time") {
      while (1) {
	getline(cin, line);
	if (line == "") break;
	vector<string> objects;
	tokenize(line, objects, "\t");
	generate_same_time_conditions(objects[0], objects[1]);
      }
    } else if (line == "people") {
      while(1) {
	getline(cin, line);
	if (line == "") 
	  break;	  

	vector<string> tokens;
	tokenize(line, tokens, "\t");
	if (tokens.size() != 4) {
	  cerr << line << endl;
	  throw "Wrong input format";
	}

	vector<string> groups;
	tokenize(tokens[0], groups, ",");
	string teacher = tokens[1];
	string subject = tokens[2];
	addTeacher(teacher);
	string classes = tokens[3];

	for (int i = 0; i < groups.size(); i++) {
	  addGroup(groups[i]);
	  generate_conditions(teacher, groups[i], subject, classes, i == 0);
	}

	if (groups.size() > 1) {
	  generate_same_time_conditions(teacher, groups, subject, classes);
	}
      }
    } else if (line == "additional") {
      cout << "// additional" << endl;
      while(1) {
	getline(cin, line);
	if (line == "") break;
	cout << line << endl;
      }
    } else if (line == "cardinality_total") {
      getline(cin, line);
      int k = atoi(line.c_str());
      // hack: izbacujemo fizicko
      auto fzc = teachers;
      fzc.erase(std::remove(fzc.begin(), fzc.end(), "steda"), fzc.end());
      fzc.erase(std::remove(fzc.begin(), fzc.end(), "rada"), fzc.end());
      generate_cardinality_constraints(fzc, k, "_people_");
    } else if (line == "cardinality_alltime") {
      vector<string> cr;
      while(1) {
	getline(cin, line);
	if (line == "") break;
	cr.push_back(line);
      }
      getline(cin, line);
      int k = atoi(line.c_str());
      cout << "// cardinality_rooms " << cr.size() << " : " << k << endl;
      generate_cardinality_constraints(cr, k, string("_") + to_string(room_card++) + "_");
    } else if (line == "cardinality") {
      vector<string> cr;
      while(1) {
	getline(cin, line);
	if (line == "") break;
	cr.push_back(line);
      }
      getline(cin, line);
      int k = atoi(line.c_str());
      cout << "// cardinality_once " << cr.size() << " : " << k << endl;
      generate_cardinality_constraints_new(cr, k, "once" + to_string(room_card++), "");
    }
  }

  generate_unique_group_conditions();
  generate_unique_teacher_conditions();
  generate_implications();
  generate_long_stay_conditions();
  generate_hole_conditions();
  generate_number_of_days_conditions(teachers);
  generate_number_of_days_conditions(groups);
}

int main(int argc, char *argv[]) {
  parse();
  return EXIT_SUCCESS;
}
